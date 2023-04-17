%% Pre-lab task 3 - Optimal control of pitch and travel with feedback
%% Initialization
%Using previous lab code for initialization.
labexercise2;

%% 1
%Inheriting Q and R matrices from previous lab.
A = A1;
B = B1;

% Same Q and R used for optimal trajectory (from lab 2)
Q = Q1; 
R = P1;


[K,P,e] = dlqr(A,B,Q,R);

%% 2
%Inheriting optimal states and inputs from previous lab.

p_c; %Optimal pitch input

% States: Travel, Travel Rate, Pitch, Pitch rate
x1_opt = x1;
x2_opt = x2;
x3_opt = x3;
x4_opt = x4;
x_opt = [x1 x2 x3 x4];
%Reminder variable

p_c; %The input u, turned into timeseries object for simulation.
x_traj = timeseries(x_opt, t);

%% Lab-tasks
%% Task 4

%% Same Q and R used for optimal trajectory (from lab 2) [lq1.mat]
% Q = Q1; 
% R = P1;
% 
% [K,P,e] = dlqr(A,B,Q,R);

%% Further penalty for deviations in travel [lq2.mat]
% Hypothesis: Converge faster to final point with a smaller offset.
% Q(1) = 20;
% Q(2) = 0;
% Q(3) = 0;
% Q(4) = 0;
% R = P1;
% 
% [K,P,e] = dlqr(A,B,Q,R);

%% Further penalty for deviations in inputs [lq3.mat]
% Hypothesis: Behaviour will be like in previous lab, where u* = u which
% led to drifting as trajectory didn't behave as predicted.
Q = Q1;
R = 20;

[K,P,e] = dlqr(A,B,Q,R);

%% Plot
run1 = load("lq2.mat").u_lambda_r_p_pdot;
run1_time = run1(1,:);
run1_input = run1(2,:);
run1_travel = run1(3,:);

run2 = load("lq3.mat").u_lambda_r_p_pdot;
run2_time = run2(1,:);
run2_input = run2(2,:);
run2_travel = run2(3,:);

subplot(2,2,1);
stairs(run1_time,run1_input);%,grid;
hold on;
stairs(run2_time,run2_input);
ylabel("u");
legend("High Q","High R");
title("Closed Loop");

subplot(2,2,3);
plot(run1_time,run1_travel);%,grid;
hold on;
plot(run2_time,run2_travel);
ylabel("lambda");
legend("High Q","High R");

subplot(2,2,2);
stairs(t,u)%,grid;
ylabel('u');
title("Optimized Open Loop Trajectory");

subplot(2,2,4);
plot(t,x1,'m',t,x1,'mo')%,grid;
ylabel('lambda');

sgtitle("Lab 3 - Task 4");