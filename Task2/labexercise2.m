% TTK4135 - Helicopter lab
% Hints/template for problem 2.

%% Initialization and model definition
init07; % Change this to the init file corresponding to your helicopter

% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
q = 0.12; %{0.12, 1.2, 12}
lambda_0 = 0;
lambda_f = pi;

A1 = eye(4) + delta_t*[0 1 0 0
    0 0 -K_2 0
    0 0 0 1
    0 0 -K_1*K_pp -K_1*K_pd];
B1 = delta_t*[0; 0; 0; K_1*K_pp];

% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x0 = [x1_0 x2_0 x3_0 x4_0]';            % Initial values

% Time horizon and initialization
%from lab exercice
N  = 100;                               % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -pi/6;                        % Lower bound on control
uu 	    = pi/6;                         % Upper bound on control
%ul          = -inf;                    % Lower bound on control (no bound)
%uu          = inf;                     % Upper bound on control (no bound)

xl          = -Inf*ones(mx,1);          % Lower bound on states (no bound)
xu          = Inf*ones(mx,1);           % Upper bound on states (no bound)
xl(3)       = ul;                      % Lower bound on state x3
xu(3)       = uu;                      % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
%Isn't it supposed to be 2q??
P1 = 2*q;                               % Weight on input
Q = gen_q(Q1, P1, N, N);                % Generate Q, hint: gen_q
c = zeros(5*N,1);                       % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1, B1, N, mx, mu);       % Generate A, hint: gen_aeq
beq = [A1*x0; zeros((4*N)-4,1)];        % Generate b

%% Solve QP problem with linear model
tic
[z,lambda] = quadprog(Q,[],[],[],Aeq,beq,vlb,vub); % hint: quadprog. Type 'doc quadprog' for more info 
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu)];    % Control input from solution

x1 = [x0(1);z(1:mx:N*mx)];                  % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];                  % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];                  % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];                  % State x4 from solution

num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u   = [zero_padding; u; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];

%% Plotting
t = 0:delta_t:delta_t*(length(u)-1);

figure(1)
subplot(511);
stairs(t,u)%,grid;
ylabel('$u$',"interpreter","latex");

subplot(512);
plot(t,x1,'m',t,x1,'mo')%,grid;
ylabel('$\lambda$',"interpreter","latex");

subplot(513);
plot(t,x2,'m',t,x2','mo')%,grid;
ylabel('$r$',"interpreter","latex");

subplot(514);
plot(t,x3,'m',t,x3,'mo')%,grid;
ylabel('$p$',"interpreter","latex");

subplot(515);
plot(t,x4,'m',t,x4','mo')%,grid;
xlabel('time ($s$)',"interpreter","latex")
ylabel('$\dot{p}$',"interpreter","latex");

sgtitle("Input unconstrained, State constrained, $q$ = "+q,"interpreter","latex");

%% Timeseries object

p_c = timeseries(u,t);

%% Extraction of timeseries

run1 = load('open_loop_run1.mat').u_lambda_r_p_pdot;
run2 = load('open_loop_run2.mat').u_lambda_r_p_pdot;

run1_time = run1(1,:);
run1_input = run1(2,:);
run1_travel = run1(3,:);
run1_traveldt = run1(4,:);
run1_pitch = run1(5,:);
run1_pitchdt = run1(6,:);

run2_time = run2(1,:);
run2_input = run2(2,:);
run2_travel = run2(3,:);
run2_traveldt = run2(4,:);
run2_pitch = run2(5,:);   
run2_pitchdt = run2(6,:);


figure(2)
subplot(511);
stairs(run1_time,run1_input)%,grid;
ylabel('$u$',"interpreter","latex");

subplot(512);
plot(run1_time,run1_travel,'m',run1_time,run1_travel)%,grid;
ylabel('$\lambda$',"interpreter","latex");

subplot(513);
plot(run1_time,run1_traveldt,'m',run1_time,run1_traveldt')%,grid;
ylabel('$r$',"interpreter","latex");

subplot(514);
plot(run1_time,run1_pitch,'m',run1_time,run1_pitch)%,grid;
ylabel('$p$',"interpreter","latex");

subplot(515);
plot(run1_time,run1_pitchdt,'m',run1_time,run1_pitchdt')%,grid;
xlabel('time ($s$)',"interpreter","latex")
ylabel('$\dot{p}$',"interpreter","latex");

sgtitle("Run 1, $q=1$","interpreter","latex");


figure(3)
subplot(511);
stairs(run2_time,run2_input)%,grid;
ylabel('$u$',"interpreter","latex");
subplot(512);
plot(run2_time,run2_travel,'m',run2_time,run2_travel)%,grid;
ylabel('$\lambda$',"interpreter","latex");
subplot(513);
plot(run2_time,run2_traveldt,'m',run2_time,run2_traveldt')%,grid;
ylabel('$r$',"interpreter","latex");
subplot(514);
plot(run2_time,run2_pitch,'m',run2_time,run2_pitch)%,grid;
ylabel('$p$',"interpreter","latex");
subplot(515);
plot(run2_time,run2_pitchdt,'m',run2_time,run2_pitchdt')%,grid;
xlabel('time ($s$)',"interpreter","latex")
ylabel('$\dot{p}$',"interpreter","latex");

sgtitle("Run 2, $q=1$","interpreter","latex");
