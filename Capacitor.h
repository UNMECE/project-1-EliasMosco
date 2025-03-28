struct _capacitor
{
    public:
  double *time;       // time array
  double *voltage;    // voltage array
  double *current;    // current array
  double C;           // capacitance value

  //return voltage, current, according to time.
};
typedef struct _capacitor Capacitor;
 void InitCapacitor( Capacitor &cap, int totalSteps, double c);
 void FreeCapacitor( Capacitor &cap);
