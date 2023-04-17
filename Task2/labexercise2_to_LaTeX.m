% TTK4135 - Helicopter lab - Exercise 2
%% Initialization and model definition
init07;

h = 0.25;
q = 1;

A_c = [0 1 0 0
    0 0 -K_2 0
    0 0 0 1
    0 0 -K_1*K_pp -K_1*K_pd];
b_c = [0; 0; 0; K_1*K_pp];

A_d = eye(4) + h*A_c;
b_d = h*b_c;

nx = size(A_d,2); %Num of states
nu = size(b_d,2); %Num of inputs

x1_0 = pi;
x2_0 = 0;
x3_0 = 0;
x4_0 = 0;
x0 = [x1_0 x2_0 x3_0 x4_0]';

N  = 100;
M  = N;
z  = zeros(N*nx+M*nu,1);
z0 = z;

p_constr = pi/6;
ul 	    = -p_constr;
uu 	    = p_constr;
%ul          = -inf;
%uu          = inf;
xl          = -Inf*ones(nx,1);
xu          = Inf*ones(nx,1);
xl(3)       = -p_constr;
xu(3)       = p_constr;

[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu);
vlb(N*nx+M*nu)  = 0;
vub(N*nx+M*nu)  = 0;

Q = zeros(nx,nx);
Q(1,1) = 2;
Q(2,2) = 0;
Q(3,3) = 0;
Q(4,4) = 0;

R = 2*q;
G = gen_q(Q, R, N, N);
c = zeros(5*N,1);
%% Generate system matrixes for linear model
Aeq = gen_aeq(A_d, b_d, N, nx, nu);
beq = [A_d*x0; zeros((4*N)-4,1)];
%% Solve QP problem with linear model
tic
[z,lambda] = quadprog(G,[],[],[],Aeq,beq,vlb,vub);
t1=toc;

phi = 0.0;
PhiOut = zeros(N*nx+M*nu,1);
for i=1:N*nx+M*nu
  phi=phi+G(i,i)*z(i)*z(i);
  PhiOut(i) = phi;
end
%% Extract control inputs and states
u  = [z(N*nx+1:N*nx+M*nu);z(N*nx+M*nu)];
x1 = [x0(1);z(1:nx:N*nx)];
x2 = [x0(2);z(2:nx:N*nx)];
x3 = [x0(3);z(3:nx:N*nx)];
x4 = [x0(4);z(4:nx:N*nx)];

num_variables = 5/h;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u   = [zero_padding; u; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];

p_c = timeseries(u,t);