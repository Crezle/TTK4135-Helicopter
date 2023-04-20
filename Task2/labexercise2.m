% TTK4135 - Helicopter lab - Exercise 2
%% Initialization and model definition
init07;

% Discrete time system model. x = [lambda r p p_dot]'
h	= 0.25;                             % sampling time
q = 0.12;                                  % {0.12, 1.2, 12} for simulation
                                        % q = 1 for helicopter run
% Continuous state space matrices
A_c = [0 1 0 0
    0 0 -K_2 0
    0 0 0 1
    0 0 -K_1*K_pp -K_1*K_pd];
b_c = [0; 0; 0; K_1*K_pp];

% Discretized state space matrices
A_d = eye(4) + h*A_c;
b_d = h*b_c;

% Number of states and inputs
nx = size(A_d,2);                       % Number of states (number of columns in A)
nu = size(b_d,2);                       % Number of inputs (number of columns in B)

% Initial values
x1_0 = pi;                                      % lambda
x2_0 = 0;                                       % r
x3_0 = 0;                                       % p
x4_0 = 0;                                       % p_dot
x0 = [x1_0 x2_0 x3_0 x4_0]';                    % Initial state vector

% Time horizon and initialization from lab exercice
N  = 100;                                       % Time horizon for states
M  = N;                                         % Time horizon for inputs
z  = zeros(N*nx+M*nu,1);                        % Initialize z for the whole horizon
z0 = z;                                         % Initial value for optimization

% Bounds
p_constr = pi/6;
ul 	    = -p_constr;                            % Lower bound on control
uu 	    = p_constr;                             % Upper bound on control
%ul          = -inf;                            % Lower bound on control (no bound)
%uu          = inf;                             % Upper bound on control (no bound)

xl          = -Inf*ones(nx,1);                  % Lower bound on states (no bound)
xu          = Inf*ones(nx,1);                   % Upper bound on states (no bound)
xl(3)       = -p_constr;                        % Add Lower bound on state x3
xu(3)       = p_constr;                         % Add Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu);
vlb(N*nx+M*nu)  = 0;                            % We want the last input to be zero
vub(N*nx+M*nu)  = 0;                            % We want the last input to be zero

% Generate the matrix G and the vector c (objecitve function weights in the QP problem) 
Q = zeros(nx,nx);
Q(1,1) = 2;                                 % Weight on state x1
Q(2,2) = 0;                                 % Weight on state x2
Q(3,3) = 0;                                 % Weight on state x3
Q(4,4) = 0;                                 % Weight on state x4
%Isn't it supposed to be 2q??
R = 2*q;                                    % Weight on input
G = gen_q(Q, R, N, N);                      % Generate G, hint: gen_q
c = zeros(5*N,1);                           % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A_d, b_d, N, nx, nu);         % Generate A
beq = [A_d*x0; zeros((4*N)-4,1)];           % Generate b

%% Solve QP problem with linear model
tic
[z,lambda] = quadprog(G,[],[],[],Aeq,beq,vlb,vub);
t1=toc;

% Calculate objective value
phi = 0.0;
PhiOut = zeros(N*nx+M*nu,1);
for i=1:N*nx+M*nu
  phi=phi+G(i,i)*z(i)*z(i);
  PhiOut(i) = phi;
end

%% Extract control inputs and states
u  = [z(N*nx+1:N*nx+M*nu);z(N*nx+M*nu)];    % Control input from solution

x1 = [x0(1);z(1:nx:N*nx)];                  % State x1 from solution
x2 = [x0(2);z(2:nx:N*nx)];                  % State x2 from solution
x3 = [x0(3);z(3:nx:N*nx)];                  % State x3 from solution
x4 = [x0(4);z(4:nx:N*nx)];                  % State x4 from solution

num_variables = 5/h;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u   = [zero_padding; u; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];

%% Timeseries object for simulink

t = 0:h:h*(length(u)-1);
p_c = timeseries(u,t);

%% Save calculated data
data = [t; u'; x1'; x2'; x3'; x4'];
save("Data/traj_based_on_q_X","t","u","x1","x2","x3","x4");
%% Plot quadprog results

% figure(1)
% subplot(511);
% stairs(t,u);
% grid on; grid minor;
% ylabel('$u$',"interpreter","latex");
% 
% subplot(512);
% plot(t,x1,'m',t,x1,'mo');
% grid on; grid minor;
% ylabel('$\lambda$',"interpreter","latex");
% 
% subplot(513);
% plot(t,x2,'m',t,x2','mo');
% grid on; grid minor;
% ylabel('$r$',"interpreter","latex");
% 
% subplot(514);
% plot(t,x3,'m',t,x3,'mo');
% grid on; grid minor;
% ylabel('$p$',"interpreter","latex");
% 
% subplot(515);
% plot(t,x4,'m',t,x4','mo');
% grid on; grid minor;
% xlabel('time ($s$)',"interpreter","latex")
% ylabel('$\dot{p}$',"interpreter","latex");
% 
% sgtitle("State and Input constrained, $q$ = " + q + ",\quad $\phi$ = " + phi,"interpreter","latex");
% 

