%% TTK4135 - Helicopter lab - Exercise 4
%% Constants
init07;

delta_t = 0.25;
N = 15;
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
lambda_f = 0;
q1 = 1;
q2 = 1;
params = [q1 q2 N lambda_f alpha beta lambda_t];

%% System matrices

% Task 1)
Ac = [0 1 0 0 0 0;
    0 0 -K_2 0 0 0;
    0 0 0 1 0 0;
    0 0 -K_1*K_pp -K_2*K_pd 0 0;
    0 0 0 0 0 1;
    0 0 0 0 -K_3*K_ep -K_3*K_ed];

Bc = [0 0;
    0 0;
    0 0;
    K_1*K_pp 0;
    0 0;
    0 K_3*K_ep];

n_x = size(Ac,2);
n_u = size(Bc,2);

% Task 2)
Ad = eye(n_x) + delta_t*Ac;
Bd = delta_t*Bc;

x0 = zeros(6,1);
x0(1) = pi;

x0_prog = zeros(N*(n_x+n_u),1);

% Task 3)
ul 	    = [-pi/6; -pi/6];                   % Lower bound on control
uu 	    = [pi/6; pi/6];                   % Upper bound on control

xl      = -Inf*ones(n_x,1);              % Lower bound on states (no bound)
xu      = Inf*ones(n_x,1);               % Upper bound on states (no bound)

[vlb,vub] = gen_constraints(N,N,xl,xu,ul,uu);

Aeq = gen_aeq(Ad,Bd,N,n_x,n_u);
    
beq = [Ad*x0; zeros((n_x*N)-n_x,1)];

Q = [1 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0];
    
R = [q1 0;
        0 q2];
    
G = gen_q(Q,R,N,N);
    
z = fmincon(@(x)obj_fun(x,params),x0_prog,[],[],Aeq,beq,vlb,vub,@(x)nonlcon(x,params));


%% Functions
function cost = obj_fun(x,params)
    q1 = params(1);
    q2 = params(2);
    N = params(3);
    lambda_f = params(4);
    
    for i = 1:N
        x(6*i - 5) = x(6*i - 5) - lambda_f; %To create (lambda - lambda_f)
    end
    
    Q = [1 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0;
        0 0 0 0 0 0];
    
    R = [q1 0;
        0 q2];
    
    G = gen_q(Q,R,N,N);
    
    cost = x'*G*x;
end

function [c,ceq] = nonlcon(x,params)
    N = params(3);
    alpha = params(5);
    beta = params(6);
    lambda_t = params(7);
    
    for i = 1:N % n_x = 6
        x(6*i - 5) = x(6*i - 5) - lambda_t; %To create (lambda - lambda_f)
    end
    
    c = zeros(1,N);
    ceq = c;
    for j = 1:N
        c(j) = alpha*exp(-beta*x(6*j - 5)^2) - x(6*j - 1);
        ceq(j) = 0;
    end
    
end