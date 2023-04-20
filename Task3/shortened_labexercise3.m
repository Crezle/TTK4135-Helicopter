% TTK4135 - Helicopter lab - Exercise 3
%% Initialization
%Using previous lab code for initialization.
labexercise2;

A_d;
b_d;

x1_opt = x1;    % Travel
x2_opt = x2;    % Travel rate
x3_opt = x3;    % Pitch
x4_opt = x4;    % Pitch rate
x_opt = [x1 x2 x3 x4];

%% Q and R matrices to be used to calculate K
Q = eye(nx); 
R = eye(nu);

%% Values to be sent to simulink

t;
p_c;
x_traj = timeseries(x_opt, t);
[K,P,e] = dlqr(A_d,b_d,Q,R);
