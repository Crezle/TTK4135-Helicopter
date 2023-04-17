labexercise2;
% redifining t to have 30 secs plotted
plot_time = 30;
t = 0:delta_t:plot_time;
delta_t_meas = 0.002;
meas_end_indice = plot_time/delta_t_meas;

figure(1);

run0 = load("lq1.mat").u_lambda_r_p_pdot;
run0_time = run0(1,1:meas_end_indice);
run0_input = run0(2,1:meas_end_indice);
run0_travel = run0(3,1:meas_end_indice);

run1 = load("lq2.mat").u_lambda_r_p_pdot;
run1_time = run1(1,1:meas_end_indice);
run1_input = run1(2,1:meas_end_indice);
run1_travel = run1(3,1:meas_end_indice);
run1_r = run1(4,1:meas_end_indice);
run1_p = run1(5,1:meas_end_indice);
run1_pdot = run1(6,1:meas_end_indice);

run2 = load("lq3.mat").u_lambda_r_p_pdot;
run2_time = run2(1,1:meas_end_indice);
run2_input = run2(2,1:meas_end_indice);
run2_travel = run2(3,1:meas_end_indice);

tiled = tiledlayout(2,2);
tiled.TileSpacing = 'compact';
tiled.Padding = 'compact';

%ax1 = subplot(2,2,1);
ax1 = nexttile;
stairs(run0_time(1:10:end),rad2deg(run0_input(1:10:end))),grid;
hold on;
stairs(run1_time(1:10:end),rad2deg(run1_input(1:10:end)));%,grid;
hold on;
stairs(run2_time(1:10:end),rad2deg(run2_input(1:10:end)));
xlabel('time [s]');
ylabel("u [deg]");
ylim([-35 35]);
hd = legend("Equal","High Q","High R");
set(hd, 'Interpreter','latex')
title("Closed Loop");

%ax2 = subplot(2,2,2);
ax2 = nexttile;
stairs(t,rad2deg(u(1:length(t),1))),grid;
xlabel('time [s]');
ylabel('u [deg]');
ylim([-35 35]);
legend("u_{opt}");
title("Optimized Open Loop Trajectory");

%ax3 = subplot(2,2,3);
ax3 = nexttile;
plot(run0_time,rad2deg(run0_travel)),grid;
hold on;
plot(run1_time,rad2deg(run1_travel));%,grid;
hold on;
plot(run2_time,rad2deg(run2_travel));
xlabel('time [s]');
ylabel("\lambda  [deg]");
ylim([-25 200]);
hl = legend("Equal","High Q","High R");
set(hl, 'Interpreter','latex')

%ax4 = subplot(2,2,4);
ax4 = nexttile;
plot(t,rad2deg(x1(1:length(t),1)), 'm'),grid;
%hold('on');
%plot(t,rad2deg(x1(1:length(t),1)), 'mo');
ylim([-25 200]);
legend("\lambda_{opt}");
xlabel('time [s]');
ylabel('\lambda [deg]');

set([ax1,ax2], 'YTick', -50:10:50);
set([ax3,ax4], 'YTick', -200:25:200);
set([ax1,ax2,ax3,ax4], 'XTick', 0:5:200);
linkaxes([ax1,ax2,ax3,ax4],'x');
linkaxes([ax1,ax2],'y');
linkaxes([ax3,ax4],'y');

sgtitle("Lab 3 - Task 4");

%set(gcf,'Position',[50 50 600 600]);   
print('-depsc2','-r600','lab3_task4.eps') % save eps. 