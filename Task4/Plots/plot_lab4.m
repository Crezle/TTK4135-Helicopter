num_of_runs = 9;

delta_t = 0.25;	
sim_time = 20;
init_time = 5;
sample_time = 0.002;
datapoints = sim_time/sample_time;
traj_datapoints = sim_time/delta_t;
init_points = init_time/sample_time;
traj_init_points = init_time/delta_t; %Accounting for x0 also

ratio = delta_t / sample_time;

task4_traj = load("../Data/task4_traj.mat").task4_traj;
t_traj = task4_traj(1,traj_init_points:traj_datapoints);
p_c_traj = task4_traj(2,traj_init_points:traj_datapoints);
e_c_traj = task4_traj(3,traj_init_points:traj_datapoints);
lambda_traj = task4_traj(4,traj_init_points:traj_datapoints);
r_traj = task4_traj(5,traj_init_points:traj_datapoints);
p_traj = task4_traj(6,traj_init_points:traj_datapoints);
pdot_traj = task4_traj(7,traj_init_points:traj_datapoints);
e_traj = task4_traj(8,traj_init_points:traj_datapoints);
edot_traj = task4_traj(9,traj_init_points:traj_datapoints);

clf;
figure(1);

lambda_constraint = linspace(0,pi,61);
e_constraint = 0.2*exp(-20*(lambda_constraint - 2*pi/3).^2);

for i=1:num_of_runs

    task4_run = load("../Data/task4_" + i + ".mat").pc_ec_lambda_r_p_pdot_e_edot;
    t = task4_run(1,init_points:ratio:datapoints);
    p_c = task4_run(2,init_points:ratio:datapoints);
    e_c = task4_run(3,init_points:ratio:datapoints);
    lambda = task4_run(4,init_points:ratio:datapoints);
    r = task4_run(5,init_points:ratio:datapoints);
    p = task4_run(6,init_points:ratio:datapoints);
    pdot = task4_run(7,init_points:ratio:datapoints);
    e = task4_run(8,init_points:ratio:datapoints);
    edot = task4_run(9,init_points:ratio:datapoints);

    if i == 1
        subplot(3,1,1);
        plot(t,rad2deg(lambda)); grid on; grid minor; hold on;
        Legend1=Cell(num_of_runs+1,1);
        Legend1{1}="Calculated trajectory";
        Legend1{i+1}="Actual trajectory, Run " + i;
        title("Travel");
        
        subplot(3,1,2);
        plot(t_traj,rad2deg(e_traj)); grid on; grid minor; hold on;
        Legend2=Cell(num_of_runs+1,1);
        Legend2{1}="Calculated trajectory";
        Legend2{i+1}="Actual trajectory, Run " + i;
        title("Elevation");
        
        subplot(3,1,3);
        plot(rad2deg(lambda_traj),rad2deg(e_traj)); grid on; grid minor; hold on;
        plot(rad2deg(lambda_constraint),rad2deg(e_constraint));
        Legend3=Cell(num_of_runs+2,1);
        Legend3{1}="Calculated trajectory";
        Legend3{2}="Constraint";
        Legend3{i+2}="Actual trajectory, Run " + i;
        title("Helicopter trajectory");
    elseif i == num_of_runs
        subplot(3,1,1);
        plot(t,rad2deg(lambda)); grid on; grid minor; hold on;
        Legend1{i+1}="Actual trajectory, Run " + i;
        legend(Legend1);
        title("Travel");
        
        subplot(3,1,2);
        plot(t_traj,rad2deg(e_traj)); grid on; grid minor; hold on;
        Legend2{i+1}="Actual trajectory, Run " + i;
        legend(Legend2);
        title("Elevation");
        
        subplot(3,1,3);
        plot(rad2deg(lambda_traj),rad2deg(e_traj)); grid on; grid minor; hold on;
        plot(rad2deg(lambda_constraint),rad2deg(e_constraint));
        Legend3{i+2}="Actual trajectory, Run " + i;
        legend(Legend3);
        title("Helicopter trajectory");
    else
        subplot(3,1,1);
        plot(t,rad2deg(lambda)); grid on; grid minor; hold on;
        %plot(t_traj,rad2deg(lambda_traj));
        legappend("Actual trajectory, Run " + i);
        %legend("Actual trajectory, Run " + i, "Calculated trajectory")
        %title("Travel");
        
        subplot(3,1,2);
        plot(t,rad2deg(e)); grid on; grid minor; hold on;
        %plot(t_traj,rad2deg(e_traj));
        legappend("Actual trajectory, Run " + i);
        %legend("Actual trajectory, Run " + i, "Calculated trajectory")
        %title("Elevation");
        
        subplot(3,1,3);
        plot(rad2deg(lambda),rad2deg(e)); grid on; grid minor; hold on;
        %plot(rad2deg(lambda_traj),rad2deg(e_traj));
        %plot(rad2deg(lambda_constraint),rad2deg(e_constraint));
        Legend3{i+2}="Actual trajectory, Run " + i;
        %legend("Actual trajectory, Run " + i, "Calculated trajectory", "Constraint");
        %title("Helicopter trajectory");
    end

    
    
    
    
    
    sgtitle("Run " + i);

end
