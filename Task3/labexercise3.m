%% Pre-lab task 3 - Optimal control of pitch and travel with feedback
%% Initialization
%Using previous lab code for initialization.
labexercise2;

%Inheriting A and B matrices from previous lab.
A = A1;
B = B1;

%Inheriting optimal states and inputs from previous lab.

p_c; %Optimal pitch input

x1_opt = x1;    % Travel
x2_opt = x2;    % Travel rate
x3_opt = x3;    % Pitch
x4_opt = x4;    % Pitch rate
x_opt = [x1 x2 x3 x4];
%Reminder variable
p_c;    %Optimal pitch input

%The input u, turned into timeseries object for simulation.
x_traj = timeseries(x_opt, t);

%% Lab Task 4
% to redo a run, outcomment the wanted Q and R definitions and run again
%% Same Q and R used for optimal trajectory (from lab 2) [lq1.mat]
% Q = Q1; 
% R = P1;

%% Further penalty for deviations in travel [lq2.mat]
% Hypothesis: Converge faster to final point with a smaller offset.
% Q = zeros(4,4)
% Q(1,1) = 20;    % weight for travel
% R = 2;

%% Further penalty for deviations in inputs [lq3.mat]
% Hypothesis: Behaviour will be like in previous lab, where u* = u which
% led to drifting as trajectory didn't behave as predicted.
Q = zeros(4,4);
Q(1,1) = 20;    % weight for travel
R = 20;

%% Calculating LQ-controller
[K,P,e] = dlqr(A,B,Q,R);  % K is used in Simulink for feedback
