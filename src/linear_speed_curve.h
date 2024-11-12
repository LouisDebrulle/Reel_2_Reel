class lin_speed_curve {
  public:
    int* times;
    int* speeds;
    int numPoints;

    lin_speed_curve(int* timeArray, int* speedArray, int size) {
      times = timeArray;
      speeds = speedArray;
      numPoints = size;
    }

    int getSpeedAtTime(int time) {
      if (time <= times[0]) {
        return speeds[0]; 
      }

      if (time >= times[numPoints - 1]) {
        return speeds[numPoints - 1];
      }

      for (int i = 1; i < numPoints; i++) {
        if (time < times[i]) {
          int t1 = times[i - 1];
          int t2 = times[i];
          int s1 = speeds[i - 1];
          int s2 = speeds[i];

          // Use floating-point for intermediate calculations
          float speed = s1 + (float)(s2 - s1) * (time - t1) / (t2 - t1);
          return (int)speed;  // Convert back to int for return
        }
      }

      return speeds[numPoints - 1]; 
    }
};
