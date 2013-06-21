void slvsml(double **u, double **rhs, double c, double dt, double **s)
/* 
   Solution of the model problem on the coarsest grid, where h = 1
   2 . The right-hand side is input
   in rhs[1..3][1..3] and the solution is returned in u[1..3][1..3].
*/
{
  void fill0(double **u, int n);


  double h=0.5;
  c=c/(h*h);
  fill0(u,3);
  u[2][2] = (rhs[2][2]+dt*s[2][2])/(1+4.0*c);
}
