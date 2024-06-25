void setAngle(double q, int n){
  double Q = q*(180/3.14);
  if(n==1||n==2||n==7||n==11||n==13||n==14)
    Q=NormalMotorPosition[n]-Q;
  else
    Q=NormalMotorPosition[n]+Q;
  if(Q>180)
    Q=Q-180;
  FinalMotorPosition[n]=Q;
}


void invKin(double px, double py, double pz, int l){
  double R1=sqrt(px*px+py*py)-a1;
  double R2=sqrt(R1*R1+pz*pz);
  double q1=atan(py/px);
  double q2=atan(pz/R1)+acos((a2*a2+R2*R2-a3*a3)/(2*a2*R2));
  double q3=acos((R2*R2-a2*a2-a3*a3)/(2*a2*a3));
  setAngle(q3,4*l+1);
  setAngle(q2,4*l+2);
  setAngle(q1,4*l+3);
}
