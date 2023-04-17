% TTK4135 - Helicopter lab
% Hints/template for problem 4.
%% Initialization and model definition
init07; % Change this to the init file corresponding to your helicopter

% Discrete time system model. x = [lambda r p p_dot]'
delta_t = 0.25;	
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

Bc = [0 0;
    0 0;
    0 0;
    K_1*K_pp 0;
    0 0;
    0 K_3*K_ep];



mx = size(Ac,2); % Number of states (number of columns in A)
mu = size(Bc,2); % Number of inputs(number of columns in B)

Ad = eye(mx) + delta_t*Ac;
Bd = delta_t*Bc;

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
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;
z0(1) = x1_0;% Initial value for optimization

% Bounds
ul 	    = [-pi/6; -inf];                    % Lower bound on control
uu 	    = [pi/6; inf];                     % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
%xl(3)   = ul;                           % Lower bound on state x3
%xu(3)   = uu;                           % Upper bound on state x3

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
Q1(5,5) = 0;                            % Weight on state x5
Q1(6,6) = 0;                            % Weight on state x6

P1 = zeros(mu,mu);
P1(1,1) = 2*q1; %0;                           % Weight on input
P1(2,2) = 2*q2;
Q = gen_q(Q1, P1, N, M);

%% Generate system matrixes for linear model
Aeq = gen_aeq(Ad, Bd, N, mx, mu);             % Generate A, hint: gen_aeq
beq = [Ad*x0; zeros((mx*N)-mx,1)];             % Generate b

%% Solve QP problem with linear model
options = optimoptions(@fmincon,'Algorithm','sqp','MaxFunctionEvaluations',5*10^4);
params = [N lambda_f lambda_t alpha beta mx];
tic
z = fmincon(@(z)obj_fun(z,Q),z0,[],[],Aeq,beq,vlb,vub,@(x)nonlcon(x,params),options);
t1=toc;

% Calculate objective value
% phi1 = 0.0;
% PhiOut = zeros(N*mx+M*mu,1);
% for i=1:N*mx+M*mu
%   phi1=phi1+Q(i,i)*z(i)*z(i);
%   PhiOut(i) = phi1;
% end

%% Extract control inputs and states
u1 = [z(N*mx+1:mu:N*mx+M*mu-1);z(N*mx+M*mu-1)]; % Control input from solution
u2 = [z(N*mx+2:mu:N*mx+M*mu);z(N*mx+M*mu)];

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x5 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x6 from solution


num_variables = 5/delta_t;
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

t = 0:delta_t:delta_t*(length(u1)-1);

%% LQR

% Experiment 1: Task4_1.mat (needs to be cut down to 20s)
% No hypothesis, just test
% Observation: Elevation has only minor changes
Q = diag(ones(1,mx));
R = diag(ones(1,mu));

% Experiment 2: Task4_2.mat
% Hypothesis: We want to avoid avoid obstracle, in theory we would want to
% weight the elevation to avoid obstracle, but we don't take into account
% the relation between pitch and elevation. 
% Observation: We noticed that the constraint was neglected due to 
% it being too small around ~11.46 degrees or ~0.2 radians

% Observation: The helicopter followed the trajectory in terms of
% elevation, but it still does not reach the optimal trajectory.
Q = diag([1 1 1 1 20 1]);
R = diag([1 1]);

% Experiment 3: Task4_3.mat
% Hypothesis: 
% Observation: Adjusted ALPHA = 0.5 to make the helicopter reach max
% optimal elevation closer to equilibirum point as the effect of elevation
% input is smaller when elevation is high (model is linearized).
Q = diag([1 1 1 1 20 1]);
R = diag([1 1]);

% Experiment 4: Task4_4.mat
% Hypothesis: Most probably not reach right elevation, but result will be
% more visible than in (1) as the system now follows a "proper" constraint.
% ALPHA = 0.5
% Observation: Surprisingly, the helicopter followed the trajectory well.
Q = diag([1 1 1 1 1 1]);
R = diag([1 1]);
%% Optimal trajectory and input
[K,P,e] = dlqr(Ad,Bd,Q,R);

xopt = [x1 x2 x3 x4 x5 x6];
uopt = [u1 u2];

x_traj = timeseries(xopt,t);
opt_input = timeseries(uopt,t);
%% Plotting

% 
figure(2)
subplot(421);
stairs(t,u1);
grid on; grid minor;
ylabel('pc');
subplot(422);
stairs(t,u2);
grid on; grid minor;
ylabel('ec');
subplot(423);
plot(t,x1,'m',t,x1,'mo');
grid on; grid minor;
ylabel('lambda');
subplot(424);
plot(t,x2,'m',t,x2','mo');
grid on; grid minor;
ylabel('r');
subplot(425);
plot(t,x3,'m',t,x3,'mo');
grid on; grid minor;
ylabel('p');
subplot(426);
plot(t,x4,'m',t,x4,'mo');
grid on; grid minor;
xlabel('tid (s)')
ylabel('pdot');
subplot(427);
plot(t,x5,'m',t,x5,'mo')
grid on; grid minor;
xlabel('tid (s)')
ylabel('e');
subplot(428);
plot(t,x6,'m',t,x6,'mo')
grid on; grid minor;
xlabel('tid (s)')
ylabel('edot');
sgtitle("$\alpha$ = " + alpha + "$\quad \beta$ = " + beta, 'interpreter', 'latex');
%% Timeseries object

p_c = timeseries(u1,t);
p_e = timeseries(u2,t);

%% Extraction of timeseries

%run1 = load('open_loop_run1.mat').u_lambda_r_p_pdot;
%run2 = load('open_loop_run2.mat').u_lambda_r_p_pdot;

%% Functions
function cost = obj_fun(x,Q)

    cost = 0.5*x'*Q*x;
    
end

function [c,ceq] = nonlcon(x,params)
    N = params(1);
    lambda_t = params(3);
    alpha = params(4);
    beta = params(5);
    mx = params(6);
    
%    c = zeros(1,N);
%     for i = 1:N
%         c(i) = alpha*exp(-beta*x(6*i - 5)^2) - x(6*i - 1);
%     end
    c = alpha*exp(-beta*(x(1:mx:mx*N) - lambda_t).^2) - x(5:mx:mx*N);
    ceq = [];
    
end

% function x_dot = f(x,u) % x_k+1 = x_k + h*f(x,u)
%     lambda = x(1);
%     r = x(2);
%     p = x(3);
%     p_dot = x(4);
%     e = x(5);
%     e_dot = x(6);
%     pc = u(1);
%     ec = u(2);
%     
%     lambda_dot = r;
%     r_dot = -K_2*p;
%     p_dot;
%     p_ddot = K_1*K_pp*p - K_1*K_pd*K_pp*p_dot;
%     e_dot;
%     e_ddot = C_p*V_s*cos(p) + C_e*cos(e);
% end