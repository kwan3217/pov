//bezier.inc

#macro GetCoeff(R0,R1,R2,R3,A,B,C,D)
  #declare D=R0;                   
  #declare C=3*(R1-R0);
  #declare B=3*(R2-R1)-C;
  #declare A=R3-B-C-D;
#end

#macro EvalBezier(A,B,C,D,P)
  (A*pow(P,3)+B*pow(P,2)+C*P+D)
#end

#macro EvalBezierPrime(A,B,C,D,P)
  (3*A*pow(P,2)+2*B*P+C)
#end

#macro PlotBezier(A,B,C,D,R,N)
  #local K=0;
  #local P0=0;
  #while (K<N)
    sphere {
      EvalBezier(A,B,C,D,P0),R
    }
    #local P1=(K+1)/N;
    cylinder {
      EvalBezier(A,B,C,D,P0),EvalBezier(A,B,C,D,P1),R
    }
    #local P0=P1;
    #local K=K+1;
  #end
#end
      
  