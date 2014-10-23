#include <iostream>
#include <vector>

#include "Analyser.h"
#include "GeometryTools.h"
#include "Delta.h"

using namespace std;

namespace GpxAnalyser
{

Result Analyser::Analyse(const Request& request)
{
  Result result;

  result.Guid = request.Guid;
  result.AthleteId = request.AthleteId;
  result.ActivityId = request.ActivityId;
  result.Name = request.Name;
  result.MovingTime = request.MovingTime;
  result.ElapsedTime = request.ElapsedTime;
  result.StartDate = request.StartDate;
  result.DistanceInKm = request.DistanceInKm;

  // walk over the points and build the activity
  const Point* previousPoint = NULL;
  for (list<Point>::const_iterator it = request.Points.begin(), end = request.Points.end(); it != end; it++)
  {
    if (previousPoint != NULL)
    {
      result.Activity.DistanceInKm += GeometryTools::CalculateDistanceInKm(*previousPoint, *it);
    }
    result.Activity.Duration = it->Time;
    previousPoint = &(*it);
  }
  result.Activity.Points = request.Points;

  // now analyse the data for each distance
  // TODO: if necessary this is the perfect place to pthread then rejoin before returning result
  for (list<Distance>::const_iterator it = request.Distances.begin(), end = request.Distances.end(); it != end; it++)
  {
    if (it->DistanceInKm > result.Activity.DistanceInKm)
    {
      continue;
    }

    BestEffort bestEffort = this->CalculateBestEffort(*it, request.Points);
    if (bestEffort.BestEffort.Points.size() > 0)
    {
      result.BestEfforts.push_back(bestEffort);
    }
  }

  return result;
}

BestEffort Analyser::CalculateBestEffort(const Distance& distance, const list<Point>& points)
{
  cout << "calculating best effort for distance: " << distance.Name << " => " << distance.DistanceInKm << " km" << endl;

  BestEffort bestEffort;
  bestEffort.EffortDistance = distance;

  double target = distance.DistanceInKm;
  bool inTargetWindow = false;
  list<Delta> deltas;
  double deltasRunningDistance = 0.0;
  double deltasRunningDuration = 0.0;

  list<Point>::const_iterator it = points.begin();
  list<Point>::const_iterator end = points.end();

  // take a *copy* of the previous point because we use the last delta in the loop
  Point previousPoint = *it;
  it++;

  while (it != end)
  {
    // get the current point and walk forwards. Note that we might move back again later if the delta is split
    const Point& nextPoint = *it;
    it++;

    Delta proposedDelta;
    proposedDelta.Duration = nextPoint.Time - previousPoint.Time;
    proposedDelta.DistanceInKm = GeometryTools::CalculateDistanceInKm(previousPoint, nextPoint);
    proposedDelta.Start = previousPoint;
    proposedDelta.End = nextPoint;

    if (!inTargetWindow && (proposedDelta.DistanceInKm + deltasRunningDistance) >= target)
    {
      // about to reach (or breach) the target for the first time. therefore want to split the
      // new delta to fit exactly
      inTargetWindow = true;
      if ((proposedDelta.DistanceInKm + deltasRunningDistance) > target)
      {
        // update the proposed delta, start point is the same walk
        double ratio = (target - deltasRunningDistance) / proposedDelta.DistanceInKm;
        Point intermediatePoint = GeometryTools::FindIntermediatePoint(proposedDelta.Start, proposedDelta.End, ratio);
        proposedDelta.Duration = intermediatePoint.Time - previousPoint.Time;
        proposedDelta.DistanceInKm = target - deltasRunningDistance;
        // noop: proposedDelta.Start = proposedDelta.Start;
        proposedDelta.End = intermediatePoint;
        it--;
      }
      // otherwise it exactly fits so don't do anything else
    }
    else if (inTargetWindow)
    {
      Delta& earliestDelta = deltas.front();
      if (proposedDelta.DistanceInKm < earliestDelta.DistanceInKm)
      {
        // split the earliest delta and use the proposed one at the end
        double ratio = proposedDelta.DistanceInKm / earliestDelta.DistanceInKm;
        Point intermediatePoint = GeometryTools::FindIntermediatePoint(earliestDelta.Start, earliestDelta.End, ratio);

        // reduce the running totals by the amount we're chopping off
        deltasRunningDistance -= proposedDelta.DistanceInKm;
        deltasRunningDuration -= intermediatePoint.Time - earliestDelta.Start.Time;

        earliestDelta.Duration = earliestDelta.End.Time - intermediatePoint.Time;
        earliestDelta.DistanceInKm = earliestDelta.DistanceInKm - proposedDelta.DistanceInKm;
        earliestDelta.Start = intermediatePoint;
        // noop: earliestDelta.End = earliestDelta.End;

      }
      else if (proposedDelta.DistanceInKm == earliestDelta.DistanceInKm)
      {
        // proposed delta exactly replaces the earliest
        deltas.erase(deltas.begin());
        deltasRunningDistance -= earliestDelta.DistanceInKm;
        deltasRunningDuration -= earliestDelta.Duration;
      }
      else
      {
        // the proposed delta is too big. remove the earliest and split the proposed one to fit
        deltas.erase(deltas.begin());
        deltasRunningDistance -= earliestDelta.DistanceInKm;
        deltasRunningDuration -= earliestDelta.Duration;

        double ratio = earliestDelta.DistanceInKm / proposedDelta.DistanceInKm;
        Point intermediatePoint = GeometryTools::FindIntermediatePoint(proposedDelta.Start, proposedDelta.End, ratio);
        proposedDelta.Duration = intermediatePoint.Time - proposedDelta.Start.Time;
        proposedDelta.DistanceInKm = earliestDelta.DistanceInKm;
        // noop: proposedDelta.Start = proposedDelta.Start;
        proposedDelta.End = intermediatePoint;
        it--;
      }
    }
    // otherwise we're still generating deltas while we work up to the target
  
    // add the proposed delta to the end and update the previous point to the last one in the
    // running delta window
    deltas.push_back(proposedDelta);
    deltasRunningDistance += proposedDelta.DistanceInKm;
    deltasRunningDuration += proposedDelta.Duration;
    previousPoint = proposedDelta.End;

    if (inTargetWindow)
    {
      if (bestEffort.BestEffort.Points.size() == 0 || bestEffort.BestEffort.Duration > deltasRunningDuration)
      {
        // new best effort
        bestEffort.BestEffort.Duration = deltasRunningDuration;
        bestEffort.BestEffort.DistanceInKm = deltasRunningDistance;
        bestEffort.BestEffort.Points.clear();
        list<Delta>::const_iterator deltaIt = deltas.begin();
        list<Delta>::const_iterator deltaEnd = deltas.end();
        bestEffort.BestEffort.Points.push_back(deltaIt->Start);
        for (; deltaIt != deltaEnd; deltaIt++)
        {
          bestEffort.BestEffort.Points.push_back(deltaIt->End);
        }
      }
    }
  }

  return bestEffort;
}

}

