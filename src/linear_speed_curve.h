

class lin_speed_curve {
  public:
    double* times;
    double* speeds;
    int numPoints;

    lin_speed_curve(double* timeArray, double* speedArray, int size) {
      times = timeArray;
      speeds = speedArray;
      numPoints = size;
    }

    int getSpeedAtTime(double time) {
      if (time <= times[0]) {
        return 0; 
      }

      if (time >= times[numPoints - 1]) {
        return 0;
      }

      for (int i = 1; i < numPoints; i++) {
        if (time < times[i]) {
          double t1 = times[i - 1];
          double t2 = times[i];
          double s1 = speeds[i - 1];
          double s2 = speeds[i];

          double speed = s1 + (s2 - s1) * (time - t1) / (t2 - t1);
          return speed;  
        }
      }

    }
};
