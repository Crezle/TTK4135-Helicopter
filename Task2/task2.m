Th% Initialization for the helicopter assignment in TTK4135.
% Run this file before you execute QuaRC -> Build.

% Updated spring 2018, Andreas L. Flåten
% Updated Spring 2019, Joakim R. Andersen

clear all;
close all;
clc;

% The encoder for travel for Helicopter 2 is different from the rest.
travel_gain = 1; %
elevation_gain = 1; %

% Physical constants
m_h = 0.4; % Total mass of the motors.
m_g = 0.03; % Effective mass of the helicopter.
l_a = 0.65; % Distance from elevation axis to helicopter body
l_h = 0.17; % Distance from pitch axis to motor

% Moments of inertia
J_e = 2 * m_h * l_a *l_a;         % Moment of interia for elevation
J_p = 2 * ( m_h/2 * l_h * l_h);   % Moment of interia for pitch
J_t = 2 * m_h * l_a *l_a;         % Moment of interia for travel

% Identified voltage sum and difference
V_s_eq = 7.73;%6.4; % Identified equilibrium voltage sum.
V_d_eq = 0.1;%0.45; % Identified equilibrium voltage difference.

% Model parameters
K_p = m_g*9.81; % Force to lift the helicopter from the ground.
K_f = K_p/V_s_eq; % Force motor constant.
K_1 = l_h*K_f/J_p;
K_2 = K_p*l_a/J_t;
K_3 = K_f*l_a/J_e;
K_4 = K_p*l_a/J_e;
K_pp = 1;
K_pd = 1;
%% "z" contains all states and inputs for the 4 time steps
% Each state vector "x" also has five individual states "lambda", "r",
% "p" & "p_dot". z then has a total length N*(4 + 1) = 20, where 4N belongs
% to the states and N to the inputs.

q = 12;
N = 100;
h = 0.25; % Sampling time
lambda_0 = pi;
x_0 = [lambda_0; 0; 0; 0];

A_c = [0 1 0 0
    0 0 -K_2 0
    0 0 0 1
    0 0 -K_1*K_pp -K_1*K_pd];
B_c = [0; 0; 0; K_1*K_pp];

% Q and R matrices (or scalar value in this case) are given:
Q = [1 0 0 0
    0 0 0 0
    0 0 0 0
    0 0 0 0];   
R = q;

%For the sake of quadprog, we combine these
G = gen_q(Q,R,N,N);


% Computing equality constraints
A = eye(4) + h*A_c;
B = h*B_c;

Aeq = gen_aeq(A,B,N,4,1);
beq = [A*x_0; zeros((4*N)-4,1)];
% Computing inequality constraints

[lb,ub] = gen_constraints(N,N,[-inf -inf -60*pi/360 -inf]',[inf inf 60*pi/360 inf]',-inf,inf);

f = zeros(5*N,1);

z = quadprog(G,f,[],[],Aeq,beq,lb,ub);


