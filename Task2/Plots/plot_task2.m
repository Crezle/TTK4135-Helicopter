%% Extraction of timeseries and plot of helicopter runs

num_of_runs = 3;

Color = {'r','g','b'};
% State and input constrained
% State constrained
% Input constrained
clf;

for i=1:num_of_runs
    run = load("../Data/open_loop_run" + i).u_lambda_r_p_pdot; % Specify file to load

    run_time = run(1,:);
    run_input = run(2,:);
    run_travel = run(3,:);
    run_traveldt = run(4,:);
    run_pitch = run(5,:);
    run_pitchdt = run(6,:);
    
    traj = load("../Data/calculated_traj_" + i);
    
    traj_t = traj.t;
    traj_p_c = traj.u;
    traj_lambda = traj.x1;
    traj_r = traj.x2;
    traj_p = traj.x3;
    traj_pdot = traj.x4;
    
    subplot(5,1,1);
    if i==1
        plot(run_time,run_input,"LineWidth",3,"LineStyle","--","color",Color{i});
        hold on; grid on; grid minor;
    else
        plot(run_time,run_input,"LineWidth",2,"color",Color{i});
        hold on; grid on; grid minor;
        ylabel('$u$',"interpreter","latex");
        if i==num_of_runs
            legend("Run 1","Run 2","Run 3");
        end
    end
    
    subplot(5,1,2);
    plot(run_time,run_travel,"LineWidth",2,"color",Color{i});
    hold on; grid on; grid minor;
    plot(traj_t,traj_lambda,"LineWidth",2,"LineStyle",":","color",Color{i});
    ylabel('$\lambda$',"interpreter","latex");
    if i==num_of_runs
        legend("Run 1","Target 1","Run 2","Target 2","Run 3","Target 3");
    end
    
    subplot(5,1,3);
    plot(run_time,run_traveldt,"LineWidth",2,"color",Color{i});
    hold on; grid on; grid minor;
    plot(traj_t,traj_r,"LineWidth",2,"LineStyle",":","color",Color{i});
    ylabel('$r$',"interpreter","latex");
    if i==num_of_runs
        legend("Run 1","Target 1","Run 2","Target 2","Run 3","Target 3");
    end
    
    subplot(5,1,4);
    plot(run_time,run_pitch,"LineWidth",2,"color",Color{i});
    hold on; grid on; grid minor;
    plot(traj_t,traj_p,"LineWidth",2,"LineStyle",":","color",Color{i});
    ylabel('$p$',"interpreter","latex");
    if i==num_of_runs
        legend("Run 1","Target 1","Run 2","Target 2","Run 3","Target 3");
    end
    
    subplot(5,1,5);
    plot(run_time,run_pitchdt,"LineWidth",2,"color",Color{i});
    hold on; grid on; grid minor;
    plot(traj_t,traj_pdot,"LineWidth",2,"LineStyle",":","color",Color{i});
    xlabel('time $t$[s]',"interpreter","latex");
    ylabel('$\dot{p}$',"interpreter","latex");
    if i==num_of_runs
        legend("Run 1","Target 1","Run 2","Target 2","Run 3","Target 3");
    end
end

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


