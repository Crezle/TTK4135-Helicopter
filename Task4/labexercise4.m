% TTK4135 - Helicopter lab
% Hints/template for problem 4.
%% Initialization and model definition
init07; % Change this to the init file corresponding to your helicopter

% Discrete time system model. x = [lambda r p p_dot]'
h = 0.25;	
q1 = 1;
q2 = 1;
lambda_0 = 0;
lambda_f = pi;
lambda_t = 2*pi/3;
alpha = 0.2;
beta = 20;


Ac = [0 1 0 0 0 0;
    0 0 -K_2 0 0 0;
    0 0 0 1 0 0;
    0 0 -K_1*K_pp -K_1*K_pd 0 0;
    0 0 0 0 0 1;
    0 0 0 0 -K_3*K_ep -K_3*K_ed];

bc = [0 0;
    0 0;
    0 0;
    K_1*K_pp 0;
    0 0;
    0 K_3*K_ep];

nx = size(Ac,2); % Number of states (number of columns in A)
nu = size(bc,2); % Number of inputs(number of columns in B)

Ad = eye(nx) + h*Ac;
bd = h*bc;

% Number of states and inputs


% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';            % Initial values

% Time horizon and initialization
%from lab exercice
N  = 40;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*nx+M*nu,1);                % Initialize z for the whole horizon
z0 = z;
z0(1) = x1_0;% Initial value for optimization

% Bounds
ul 	    = [-pi/6; -inf];                    % Lower bound on control
uu 	    = [pi/6; inf];                     % Upper bound on control

xl      = -Inf*ones(nx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(nx,1);               % Upper bound on states (no bound)
%xl(3)   = ul;                           % Lower bound on state x3
%xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*nx+M*nu)  = 0;                    % We want the last input to be zero
vub(N*nx+M*nu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q = zeros(nx,nx);
Q(1,1) = 2;                            % Weight on state x1
Q(2,2) = 0;                            % Weight on state x2
Q(3,3) = 0;                            % Weight on state x3
Q(4,4) = 0;                            % Weight on state x4
Q(5,5) = 0;                            % Weight on state x5
Q(6,6) = 0;                            % Weight on state x6

R = zeros(nu,nu);
R(1,1) = 2*q1; %0;                           % Weight on input
R(2,2) = 2*q2;
G = gen_q(Q, R, N, M);

%% Generate system matrixes for linear model
Aeq = gen_aeq(Ad, bd, N, nx, nu);             % Generate A, hint: gen_aeq
beq = [Ad*x0; zeros((nx*N)-nx,1)];             % Generate b

%% Solve QP problem with linear model
options = optimoptions(@fmincon,'Algorithm','sqp','MaxFunctionEvaluations',5*10^4);
params = [N lambda_f lambda_t alpha beta nx];

z = fmincon(@(z)obj_fun(z,G),z0,[],[],Aeq,beq,vlb,vub,@(x)nonlcon(x,params),options);

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*nx+M*nu,1);
for i=1:N*nx+M*nu
  phi1=phi1+G(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u1 = [z(N*nx+1:nu:N*nx+M*nu-1);z(N*nx+M*nu-1)]; % Control input from solution
u2 = [z(N*nx+2:nu:N*nx+M*nu);z(N*nx+M*nu)];

x1 = [x0(1);z(1:nx:N*nx)];              % State x1 from solution
x2 = [x0(2);z(2:nx:N*nx)];              % State x2 from solution
x3 = [x0(3);z(3:nx:N*nx)];              % State x3 from solution
x4 = [x0(4);z(4:nx:N*nx)];              % State x4 from solution
x5 = [x0(5);z(5:nx:N*nx)];              % State x5 from solution
x6 = [x0(6);z(6:nx:N*nx)];              % State x6 from solution


num_variables = 5/h;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1  = [zero_padding; u1; zero_padding];
u2  = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

%% Feedback

t = 0:h:h*(length(u1)-1);
task4_traj = [t; u1'; u2'; x1'; x2'; x3'; x4'; x5'; x6'];
save("Data/task4_traj.mat","task4_traj");

%% Experiment 1: Task4_1.mat (needs to be cut down to 20s)
% No hypothesis, just test
% Observation: Elevation has only minor changes
Q = diag(ones(1,nx));
R = diag(ones(1,nu));

%% Experiment 2: Task4_2.mat (PUT IN NEW FOLDER)
% Hypothesis: We want to avoid avoid obstracle, in theory we would want to
% weight the elevation to avoid obstracle, but we don't take into account
% the relation between pitch and elevation. 
% Observation: We noticed that the constraint was neglected due to 
% it being too small around ~11.46 degrees or ~0.2 radians

% Observation: The helicopter followed the trajectory in terms of
% elevation, but it still does not reach the optimal trajectory.
Q = diag([1 1 1 1 20 1]);
R = diag([1 1]);

%% Experiment 3: Task4_3.mat (PUT IN NEW FOLDER)
% Hypothesis: 
% Observation: Adjusted ALPHA = 0.5 to make the helicopter reach max
% optimal elevation closer to equilibirum point as the effect of elevation
% input is smaller when elevation is high (model is linearized).
Q = diag([1 1 1 1 20 1]);
R = diag([1 1]);

%% Experiment 4: Task4_4.mat (PUT IN NEW FOLDER)
% Hypothesis: Most probably not reach right elevation, but result will be
% more visible than in (1) as the system now follows a "proper" constraint.
% ALPHA = 0.5
% Observation: Surprisingly, the helicopter followed the trajectory well.
%Q = diag([1 1 1 1 1 1]);
%R = diag([1 1]);

%% Experiment 5 18.04: Task4_5.mat (RENAMED: task4_2.mat)
% alpha 0.2
Q = diag([1 1 1 1 20 1]);
R = diag([1 1]);

%% Experiment 6 18.04: Task4_6.mat (RENAMED: task4_3.mat)
% alpha 0.2
Q = diag([1 1 1 1 200 1]);
R = diag([1 1]);

%% Experiment 7 18.04: Task4_7.mat (RENAMED: task4_4.mat)
% alpha 0.2
Q = diag([100 1 1 1 200 1]);
R = diag([1 1]);

%% Experiment 8 18.04: Task4_8.mat (RENAMED: task4_5.mat)
% alpha 0.2
Q = diag([100 1 1 1 200 50]);
R = diag([1 1]);

%% Experiment 9 18.04: Task4_9.mat (RENAMED: task4_6.mat)
% alpha 0.2
Q = diag([100 1 1 1 50 10]);
R = diag([1 1]);

%% Optimal trajectory and input
[K,P,e] = dlqr(Ad,bd,Q,R);

xopt = [x1 x2 x3 x4 x5 x6];
uopt = [u1 u2];

x_traj = timeseries(xopt,t);
opt_input = timeseries(uopt,t);

%% Timeseries object

p_c = timeseries(u1,t);
p_e = timeseries(u2,t);

%% Functions
function cost = obj_fun(x,G)

    cost = 0.5*x'*G*x;
    
end

function [c,ceq] = nonlcon(x,params)
    N = params(1);
    lambda_t = params(3);
    alpha = params(4);
    beta = params(5);
    nx = params(6);
    
%    c = zeros(1,N);
%     for i = 1:N
%         c(i) = alpha*exp(-beta*x(6*i - 5)^2) - x(6*i - 1);
%     end
    c = alpha*exp(-beta*(x(1:nx:nx*N) - lambda_t).^2) - x(5:nx:nx*N);
    ceq = [];
    
end
