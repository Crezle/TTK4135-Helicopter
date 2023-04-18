delta_t = 0.25;	
plot_time = 25;
t = 0:delta_t:plot_time;
delta_t_meas = 0.002;
meas_end_indice = plot_time/delta_t_meas;

task4_run1 = load("Data/task4_1.mat").pc_ec_lambda_r_p_pdot_e_edot;
task4_run1_time = task4_run1(1,1:meas_end_indice);
task4_run1_pc = task4_run1(2,1:meas_end_indice);
task4_run1_ec = task4_run1(3,1:meas_end_indice);
task4_run1_travel = task4_run1(4,1:meas_end_indice);
task4_run1_r = task4_run1(5,1:meas_end_indice);
task4_run1_p = task4_run1(6,1:meas_end_indice);
task4_run1_pdot = task4_run1(7,1:meas_end_indice);
task4_run1_e = task4_run1(8,1:meas_end_indice);
task4_run1_edot = task4_run1(9,1:meas_end_indice);

figure(1);
tiled = tiledlayout(1,2);
tiled.TileSpacing = 'compact';
tiled.Padding = 'compact';

ax1 = nexttile;
plot(task4_run1_time(1:10:end),rad2deg(task4_run1_travel(1:10:end))),grid;

xlabel('time [s]');
ylabel("\lambda [deg]");
%ylim([-35 35]);
hd = legend("Travel");
set(hd, 'Interpreter','latex')
title("Closed Loop");

ax2 = nexttile;
plot(task4_run1_time(1:10:end),rad2deg(task4_run1_e(1:10:end))),grid;

xlabel('time [s]');
ylabel("e [deg]");
%ylim([-35 35]);
hd = legend("Elevation");
set(hd, 'Interpreter','latex');
