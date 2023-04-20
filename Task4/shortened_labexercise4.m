% TTK4135 - Helicopter lab - Exercise 4
%% Initialization and model definition
init07;

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

nx = size(Ac,2); % Number of states
nu = size(bc,2); % Number of inputs

Ad = eye(nx) + h*Ac;
bd = h*bc;

% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';  % Initial values

% Time horizon and initialization
N  = 40;
M  = N;
z  = zeros(N*nx+M*nu,1);
z0 = z;
z0(1) = x1_0;% Initial value for optimization

% Bounds
ul 	    = [-pi/6; -inf];
uu 	    = [pi/6; inf];

xl      = -Inf*ones(nx,1);
xu      = Inf*ones(nx,1);
%xl(3)   = ul;              % Lower bound on state x3
%xu(3)   = uu;              % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu);
vlb(N*nx+M*nu)  = 0;
vub(N*nx+M*nu)  = 0;

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q = zeros(nx,nx);
Q(1,1) = 2;
Q(2,2) = 0;
Q(3,3) = 0;
Q(4,4) = 0;
Q(5,5) = 0;
Q(6,6) = 0;

R = zeros(nu,nu);
R(1,1) = 2*q1;
R(2,2) = 2*q2;
G = gen_q(Q, R, N, M);

%% Generate system matrixes for linear model
Aeq = gen_aeq(Ad, bd, N, nx, nu);
beq = [Ad*x0; zeros((nx*N)-nx,1)];

%% Solve QP problem with linear model
options = optimoptions(@fmincon,'Algorithm','sqp','MaxFunctionEvaluations',5*10^4);
params = [N lambda_f lambda_t alpha beta nx nu];

z = fmincon(@(z)obj_fun(z,G,params),z0,[],[],Aeq,beq,vlb,vub,@(x)nonlcon(x,params),options);

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

%% Experiment X:
% Change Q and R based on what we want to test for LQR
Q = diag(ones(1,nx));
R = diag(ones(1,nu));

%% Optimal trajectory and input
[K,P,e] = dlqr(Ad,bd,Q,R);

xopt = [x1 x2 x3 x4 x5 x6];
uopt = [u1 u2];



%% Optimal input to Simulink
t = 0:h:h*(length(u1)-1);

x_traj = timeseries(xopt,t);
opt_input = timeseries(uopt,t);

p_c = timeseries(u1,t);
p_e = timeseries(u2,t);

%% Functions
function cost = obj_fun(x,G,params)
    N = params(1);
    lambda_f = params(2);
    nu = params(7);
    
    c_temp = [-2*lambda_f 0 0 0 0 0];
    c_1 = repmat(c_temp,1,N);
    c_2 = zeros(1,N*nu);
    c = [c_1 c_2];
    
    cost = 0.5*x'*G*x + c*x;
end

function [c,ceq] = nonlcon(x,params)
    N = params(1);
    lambda_t = params(3);
    alpha = params(4);
    beta = params(5);
    nx = params(6);
    
    c = alpha*exp(-beta*(x(1:nx:nx*N) - lambda_t).^2) - x(5:nx:nx*N);
    ceq = [];
end
