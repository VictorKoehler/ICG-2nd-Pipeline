# this is a script file
1;

clear all;

################################################################################
# Vertices do modelo (cubo) no espaco do objeto.
################################################################################
v_obj(:,1) = [-1; -1; -1; 1];
v_obj(:,2) = [-1; -1;  1; 1];
v_obj(:,3) = [ 1; -1; -1; 1];
v_obj(:,4) = [ 1; -1;  1; 1];
v_obj(:,5) = [-1;  1; -1; 1];
v_obj(:,6) = [-1;  1;  1; 1];
v_obj(:,7) = [ 1;  1; -1; 1];
v_obj(:,8) = [ 1;  1;  1; 1];

################################################################################
# Arestas do modelo (indiced dos vertices).
################################################################################
# bottom
a(1).c = [1; 2];
a(2).c = [1; 3];
a(3).c = [2; 4];
a(4).c = [3; 4];

#top
a(5).c = [5; 6];
a(6).c = [5; 7];
a(7).c = [6; 8];
a(8).c = [7; 8];

# vert
a(9).c = [1; 5];
a(10).c = [2; 6];
a(11).c = [3; 7];
a(12).c = [4; 8];

################################################################################
# Matriz model
################################################################################
M_model = [ 1 0 0 0;
            0 1 0 0;
            0 0 1 0;
            0 0 0 1 ];

################################################################################
# Parametros da camera
################################################################################
camera_pos    = [1.3; 2.1; 2.5];  # Posicao da camera no universo.
camera_lookat = [0; 0; 0];  # Ponto para onde a camera esta olhando.
camera_up     = [0; 1; 0];  # 'up' da camera no espaco do universo.

################################################################################
# Calculo do sistema ortonormal gerado a partir dos parametros da camera
################################################################################

camera_dir = camera_lookat - camera_pos;

z_camera = -(camera_dir) / norm(camera_dir);
x_camera = cross(camera_up, z_camera) / norm(cross(camera_up, z_camera));
y_camera = cross(z_camera, x_camera);

################################################################################
# Construcao da matriz view
################################################################################

Bt = [x_camera(1), x_camera(2), x_camera(3), 0;
      y_camera(1), y_camera(2), y_camera(3), 0;
      z_camera(1), z_camera(2), z_camera(3), 0;
      0, 0, 0, 1];

T = [1, 0, 0, -camera_pos(1);
     0, 1, 0, -camera_pos(2);
     0, 0, 1, -camera_pos(3);
     0, 0, 0, 1];

M_view = Bt * T;

################################################################################
# Construcao da matriz de Projecao, com d = 1
################################################################################
d = 1;

M_projection = [1, 0, 0, 0;
                0, 1, 0, 0;
                0, 0, 1, d;
                0, 0, -(1/d), 0];

################################################################################
# Construcao da matriz de ModelViewProjection
################################################################################

M_model_view_proj = M_projection * M_view * M_model;

%for i = 1 : 8
%    v_clip(i) = M_model_view_proj * v_obj(i);
%endfor
v_clip = M_model_view_proj * v_obj;

################################################################################
# Homogeneizacao (divisao por W).
# Este passo leva os vertices normalmente para o espaço canonico.
# Neste caso, como a matriz de projecao eh muito simples, o resultado
# da homogeneizacao sao os vertices em um espaço que nao eh exatamente o
# canonico. Porem, apesar de nao ser o espaco canonico, a distorcao perspectiva
# estara presente.
################################################################################

%for i = 1 : 8
%    v_canonic(i) = v_clip(i) / v_clip(i)(4);
%endfor
v_canonic = v_clip ./ v_clip(4,:);

################################################################################
# Conversão de coordenadas do espaço canônico para o espaço de tela.
################################################################################

S1 = [1 0 0 0;
      0 -1 0 0;
      0 0 1 0;
      0 0 0 1];

T = [1 0 0 1;
     0 1 0 1;
     0 0 1 0;
     0 0 0 1];

w = 512;
h = 512;

S2 = [(w-1)/2 0 0 0;
      0 (h-1)/2 0 0;
      0 0 1 0;
      0 0 0 1];

M_viewport = S2 * T * S1;

%for i = 1 : 8
%    v_screen(i) = M_viewport * v_canonic(i);
%endfor

v_screen = M_viewport * v_canonic % exibe na tela

################################################################################
# Desenho da geometria na "tela"
################################################################################

clf;
grid off;
hold on;

axis([0, 512, 0, 512], "tic");
axis square;

set (gca (), "ydir", "reverse")

xlabel("X");
ylabel("Y");

for i = 1 : 12
    plot([v_screen(1, a(i).c(1)), v_screen(1, a(i).c(2))],
         [v_screen(2, a(i).c(1)), v_screen(2, a(i).c(2))], "b-");
endfor

