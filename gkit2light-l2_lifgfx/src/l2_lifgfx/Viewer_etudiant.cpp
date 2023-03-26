
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>   // pour srand() et rand() 
#include <time.h>     // pour time()

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;




//--------------------------------------------------------Définition de la procédure pour le carré---------------------------------------------------------------------------------------------------------

 


void ViewerEtudiant::init_quad()
{
    

    m_quad = Mesh(GL_TRIANGLE_STRIP);
    
    
    m_quad.normal(0, 0, 1); 

    m_quad.texcoord(0, 0); // Coordoonées pour la texture
    m_quad.vertex(-1, -1, 0); // Définition

    m_quad.texcoord(1, 0);
    m_quad.vertex(1, -1, 0);

    m_quad.texcoord(0, 1);
    m_quad.vertex(-1, 1, 0);

    m_quad.texcoord(1, 1);
    m_quad.vertex(1, 1, 0);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------Définition de la procédure pour le cube---------------------------------------------------------------------------------------------





    //       4---5
    //      /|  /|
    //     7---6 |
    //     | 0-|-1
    //     |/  |/
    //     3---2


 void ViewerEtudiant::init_cube() {

   
    //8 sommets                    0          1          2          3          4         5        6         7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };

    //6 faces                  0          1          2          3          4          5
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };

    // les 6 normales pour chacune des faces
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    // Choix des primitives OpenGL employées 
    m_cube = Mesh(GL_TRIANGLE_STRIP);

        // Parcours des 6 faces
        for (int i = 0; i < 6; i++) // i = numéro de la face
        {
            //couleur
            //m_cube.color(0.0, 0.9, 1.0); //pour colorier tout le cube en une fois.
           
            // La normale à la face
            m_cube.normal(n[i][0], n[i][1], n[i][2]);  // Coordonnées en x, y et z de la normale à la face.

            // Les 4 sommets de la face
           // m_cube.color(Color(1, 0, 0));   //colorier chaque sommet avant sa création pour avoir différentes couleurs.

            m_cube.texcoord(0,1);    // Coordonnées de texture du cube.
            m_cube.vertex(pt[f[i][0]][0], pt[f[i][0]][1], pt[f[i][0]][2]);   // Coordonnées en x, y et z du sommet 0 de la face i.

            //m_cube.color(Color(0, 1, 0));

            m_cube.texcoord(1,0);// Coordonnées de texture du cube.
            m_cube.vertex(pt[f[i][1]][0], pt[f[i][1]][1], pt[f[i][1]][2]);   // Coordonnées en x, y et z du sommet 1 de la face i.

            //m_cube.color(Color(0, 0, 1));

            m_cube.texcoord(1, 1);  // Coordonnées de texture du cube.
            m_cube.vertex(pt[f[i][3]][0], pt[f[i][3]][1], pt[f[i][3]][2]);   // Coordonnées en x, y et z du sommet 2 de la face i.

           //m_cube.color(Color(1, 1, 1));

            m_cube.texcoord(0,0);   // Coordonnées de texture du cube.
            m_cube.vertex(pt[f[i][2]][0], pt[f[i][2]][1], pt[f[i][2]][2]);   // Coordonnées en x, y et z du sommet 3 de la face i.

            m_cube.restart_strip();   // Demande un nouveau strip
        }
}
    
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------











 //----------------------------------------------Définition de la procédure pour le Cylindre---------------------------------------------------------------------------------------------

 void ViewerEtudiant::init_cylindre() 
 {

         // Variation de l’angle de 0 à 2!
         const int div = 25;
         float alpha;
         float step = 2.0 * M_PI / (div);
         // Choix primitive OpenGL
         m_cylindre = Mesh(GL_TRIANGLE_STRIP);

             for (int i = 0; i <= div; ++i)
             {
                 //couleur
                 //m_cylindre.color(1.0, 0.0, 0.1);
                 // Variation de l’angle de 0 à 2!
                 alpha = i * step;
                 m_cylindre.texcoord(i / div, 1);
                 m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
                 m_cylindre.vertex(Point(cos(alpha), -1, sin(alpha)));

                 m_cylindre.texcoord(i / div, 0);
                 m_cylindre.normal(Vector(cos(alpha), 0, sin(alpha)));
                 m_cylindre.vertex(Point(cos(alpha), 1, sin(alpha)));
             }
 }
 
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------







 //----------------------------------------------------Définition de la procédure pour le Disque-------------------------------------------------------------------


 void ViewerEtudiant::init_disque()
 {
     // Variation de l’angle de 0 à 2!
     const int div = 25;
     float alpha;
     float step = 2.0 * M_PI / (div);
     // Choix primitive OpenGL
     m_disque = Mesh(GL_TRIANGLE_FAN);
     m_disque.color(Color(0, 1, 0));//couleur
     m_disque.normal(Vector(0, 1, 0)); // Normale à la surface
     m_disque.vertex(Point(0, 0, 0));   // Point du centre du disque
     // Variation de l’angle de 0 à 2!
     for (int i = 0; i <= div; ++i)
     {
         alpha = i * step;
         m_disque.normal(Vector(0, 1, 0));
         m_disque.vertex(Point(cos(alpha), 0, sin(alpha)));
     }

 }
 
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------








  //----------------------------------------------------Définition de la procédure pour le cone-------------------------------------------------------------------


 void ViewerEtudiant::init_cone()
 {
     // Variation de l’angle de 0 à 2!
     const int div = 25;
     float alpha;
     float step = 2.0 * M_PI / (div);
     // Choix de la primitive OpenGL
     m_cone = Mesh(GL_TRIANGLE_STRIP);
     for (int i = 0;i <= div;++i)
     {
         //couleur
         //m_cone.color(0.0, 1.0, 0.1);
         alpha = i * step; // Angle varie de 0 à 2!
         m_cone.texcoord(i / div, 1);
         m_cone.normal(Vector(cos(alpha) / sqrtf(2.f), 1.f / sqrtf(2.f),sin(alpha) / sqrtf(2.f)));
         m_cone.vertex(Point(cos(alpha), 0, sin(alpha)));

         m_cone.texcoord(i / div, 0);
         m_cone.normal( Vector(cos(alpha) / sqrtf(2.f), 1.f / sqrtf(2.f), sin(alpha) / sqrtf(2.f)));
         m_cone.vertex(Point(0, 1, 0));
     }
 }
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------






 

   //----------------------------------------------------Définition de la procédure pour la sphere-------------------------------------------------------------------

 void ViewerEtudiant::init_sphere()
 {
     // Variation des angles alpha et beta
     const int divBeta = 16;
     const int divAlpha = divBeta / 2;
     float beta, alpha, alpha2;
     // Choix de la primitive OpenGL
     m_sphere = Mesh(GL_TRIANGLE_STRIP);
     // Variation des angles alpha et beta
     for (int i = 0; i < divAlpha; ++i)
     {
         //couleur
         m_sphere.color(1.0, 1.0, 1.1);

         // Nous donne un rayon et son positionnement.
         alpha = -0.5f * M_PI + float(i) * M_PI / divAlpha;

         // On considère deux cercles en mêmes-temps pour les relier en triangles donc il faut 2 alpha.
         alpha2 = -0.5f * M_PI + float(i + 1) * M_PI / divAlpha;

         for (int j = 0; j <= divBeta; ++j)  // Variation de l'angle beta : sphère -> superposition de cercles.
         {
             beta = float(j) * 2.f * M_PI / (divBeta); 
             m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha / M_PI);   //coordoonées pour les textures 
             m_sphere.normal(Vector(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));    // Normale du cercle du bas.
             m_sphere.vertex(Point(cos(alpha) * cos(beta), sin(alpha), cos(alpha) * sin(beta)));   // Points du bas.

             m_sphere.texcoord(beta / (M_PI * 2.0), 0.5 + alpha2 / M_PI);   //coordoonées pour les textures 
             m_sphere.normal(Vector(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));   // Normale du cercle du haut.
             m_sphere.vertex(Point(cos(alpha2) * cos(beta), sin(alpha2), cos(alpha2) * sin(beta)));    // Points du haut.

         } // boucle sur les j, angle beta, dessin des sommets d’un cercle

         m_sphere.restart_strip(); // Demande un nouveau strip

     } // boucle sur les i, angle alpha, sphère = superposition de cercles
 }

 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------









 //----------------------------------------------------Définition de la procédure pour le cubemap-------------------------------------------------------------------

 void ViewerEtudiant::init_cubemap()
 {
     // 8 sommets                  0            1         2         3           4        5         6         7
     static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
     // 6 faces                 0         1           2          3         4           5
     static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
     // les 6 normales pour chacune des faces
     static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {1,0,0}, {0,0,1}, {0,0,-1} };
     //les coordonées de la texture par rapport a chaque point de chaque face
     static float tc[6][4][2] = {
         {{0.25,0},         {0.5 ,0},         {0.5,1 / 3.f},        {0.25,1 / 3.f}},//premier face
         {{0.5 ,1},         {0.25,1},         {0.25,2 / 3.f},       {0.5,2 / 3.f}},
         {{0.5,1 / 3.f},    {0.75,1 / 3.f},   {0.75,2 / 3.f},       {0.5,2 / 3.f}},
         {{0,1 / 3.f},      {0.25,1 / 3.f},   {0.25,2 / 3.f},       {0,2 / 3.f}},
         {{0.25,1 / 3.f},   {0.5,1 / 3.f},    {0.5,2 / 3.f},        {0.25,2 / 3.f}},
         {{0.75,1 / 3.f},   {1,1 / 3.f},      {1,2 / 3.f},          {0.75,2 / 3.f}}//dernière face

     };
     // Choix des primitives OpenGL employées 
     m_cubemap = Mesh(GL_TRIANGLE_STRIP);

     for (int i = 0; i < 6; i++) // i = numéro de la face
     {
         // La normale à la face
         m_cubemap.normal(-n[i][0], -n[i][1], -n[i][2]);
         // Les 4 sommets de la face
         m_cubemap.texcoord(tc[i][0][0], tc[i][0][1]);
         m_cubemap.vertex(pt[f[i][0]][2], pt[f[i][0]][1], pt[f[i][0]][0]);

         m_cubemap.texcoord(tc[i][1][0], tc[i][1][1]);
         m_cubemap.vertex(pt[f[i][1]][2], pt[f[i][1]][1], pt[f[i][1]][0]);

         m_cubemap.texcoord(tc[i][3][0], tc[i][3][1]);
         m_cubemap.vertex(pt[f[i][3]][2], pt[f[i][3]][1], pt[f[i][3]][0]);

         m_cubemap.texcoord(tc[i][2][0], tc[i][2][1]);
         m_cubemap.vertex(pt[f[i][2]][2], pt[f[i][2]][1], pt[f[i][2]][0]);
         m_cubemap.restart_strip(); // Demande un nouveau strip
     }
 }

 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------







 

 
     
 //-----------------------------------------------Terrain------------------------------------------------------------------------------------------------------------------

 Vector TerrainNormal(const Image& im, const int i, const int j) {

     //Calcul de la normale au point(i,j) de l'image
     int ip = i - 1;
     int in = i + 1;
     int jp = j - 1;
     int jn = j + 1;


     // On définit chacun de ses points.
     Vector a(ip, im(ip, j).r, j);
     Vector b(in, im(in, j).r, j);
     Vector c(i, im(i, jp).r, jp);
     Vector d(i, im(i, jn).r, jn);

     Vector ab = normalize(b - a);
     Vector cd = normalize(d - c);

     // On fait le produit vectoriel.
     Vector n = cross(cd, ab);

     return n;
 }






 //Initialisation du terrain
 void ViewerEtudiant::init_terrain(Mesh& m_terrain, const Image& im) {

     
     m_terrain = Mesh(GL_TRIANGLE_STRIP); //Choix primitive OpenGL



     for (int i = 1;i < im.width() - 2;++i) { //Boucle sur les i.


         for (int j = 1;j < im.height() - 1;++j) { // Boucle sur les j


             m_terrain.normal(TerrainNormal(im, i + 1, j));    // Calcul de la normal en (i+1, j).
             m_terrain.texcoord((float)i / (im.width() - 2), (float)j / (im.height() - 1));    // Coordonnées de textures par rapport à l'image.
             m_terrain.vertex(Point(i + 1, 25.f * im(i + 1, j).r, j));   // Sommet à partir du point (i+1, j) de mon image.


             m_terrain.normal(TerrainNormal(im, i, j));   // Calcul de la normal en (i, j).
             m_terrain.texcoord((float)i / (im.width() - 2), (float)j / (im.height() - 1));  // Coordonnées de textures par rapport à l'image.
             m_terrain.vertex(Point(i, 25.f * im(i, j).r, j));   // Sommet à partir du point (i, j) de mon image.
         }
         
         m_terrain.restart_strip(); //Affichage en triangle_strip par bande
     }
 }


 //---------------------------------------------------------------------------------------------------------------------------------------------------------------------





 //------------------------------------------------------ARBRE init-----------------------------------------------------------------------------------------------------
 void ViewerEtudiant::init_tree(const Image& im)
 {

     srand((unsigned int)time(NULL));
     
         for (int w = 0; w < 10; w++)     //boucle pour remplir le tableau qu'on a déclaré dans Viewer.h avec les coordoonées (x,y,z)   
     {
         TabPosition[w][0] = rand() % (im.width() - 2); // coordoonées de x qui varie au hasard entre 0 et (im.width() - 2) 
         TabPosition[w][2] = rand() % (im.height() - 1); //coordoonées de y qui varie au hasard entre 0 et  (im.height() - 1) qui represente la hauteur des arbres en fonction de la texture du terrain
         TabPosition[w][1] = 25.f * im(TabPosition[w][0], TabPosition[w][2]).r; // coordoonées de z qui varie e focntion des valeurs de x et y

     }
     

 }
 //-----------------------------------------------------------------------------------------------------------------------------------------------------------
 
 
 
 
 




 //Texture animée : Question 5

 //-----------------------------------------------------------------------------------------------------------------------------------------------------------
 void  ViewerEtudiant::init_mouette1()
 {
     m_mouette1 = Mesh(GL_TRIANGLE_STRIP);

     m_mouette1.normal(0, 0, 3.5);

     m_mouette1.texcoord(0, 0);
     m_mouette1.vertex(-3.5, -3.5, 0);

     m_mouette1.texcoord(1, 0);
     m_mouette1.vertex(3.5, -3.5, 0);

     m_mouette1.texcoord(0, 1);
     m_mouette1.vertex(-3.5, 3.5, 0);

     m_mouette1.texcoord(1, 1);
     m_mouette1.vertex(3.5, 3.5, 0);

 }

 //-----------------------------------------------------------------------------------------------------------------------------------------------------------


 //--------------------------------------------------Modélisation d'un objet par extrusion----------------------------------------------------------------------------------------------------------------------------------
 
 //extrusion vase

 void ViewerEtudiant::create_vertex_normal_vase() {

     // Nombre de points de la silhouette 2D

     vase_NBPT = 10; // déclaré dans la class ViewerEtudiant

     /// Points de la silhouette 2D
     vase_p[0] = Point(0.3, 0, 0);
     vase_p[1] = Point(0.2, 0.2, 0);
     vase_p[2] = Point(0.4, 0.4, 0);
     vase_p[3] = Point(0.5, 0.6, 0);
     vase_p[4] = Point(0.6, 0.8, 0);
     vase_p[5] = Point(0.7, 1.0, 0);
     vase_p[6] = Point(0.8, 1.2, 0);
     vase_p[7] = Point(0.8, 1.4, 0);
     vase_p[8] = Point(0.8, 1.6, 0);
     vase_p[9] = Point(0.5, 1.8, 0);

     // Nombre de rotations pour créer le vase par rotation
     vase_NBROT = 20; // déclaré dans la class ViewerEtudiant

     for (int i = 0; i < vase_NBROT; i++) {

         //i indice rotation (angle : 2 pi * i / nbrot)
         
         // Angle qui varie de 0 à 2 pi
         float teta = 2 * M_PI * i / vase_NBROT;

         // Matrice de rotation de l’angle theta autour axe des y


         
         // en coordonnées homogènes : 4 x 4
         float mat[16] = {
         cos(teta), 0, -sin(teta), 0, 0, 1, 0, 0, sin(teta), 0, cos(teta), 0, 0, 0, 0, 1 };



         // Calcul des coordonnées des sommets
         for (int j = 0; j < vase_NBPT; j++) {
             // j indice du point de la silhouette
             
             
             // Application de ma matrice de rotation au point j qui subit la rotation (2 pi * i / nbrot)
             vase_v[i][j].x = mat[0] * vase_p[j].x + mat[1] * vase_p[j].y + mat[2] * vase_p[j].z + mat[3] * 1;
             vase_v[i][j].y = mat[4] * vase_p[j].x + mat[5] * vase_p[j].y + mat[6] * vase_p[j].z + mat[7] * 1;
             vase_v[i][j].z = mat[8] * vase_p[j].x + mat[9] * vase_p[j].y + mat[10] * vase_p[j].z + mat[11] * 1;
         }    //for_j
     }    //for_i

 // Initialise à 0 les normales

     for (int i = 0; i < vase_NBROT; i++)

         for (int j = 0; j < vase_NBPT; j++)

             vase_vn[i][j] = Vector(0, 0, 0);

     for (int i = 0; i < vase_NBROT; i++) {

         for (int j = 0; j < vase_NBPT - 1; j++) {

             Vector a, b, vntmp;
             a = normalize(vase_v[i][j] - vase_v[i][j + 1]);
             b = normalize(vase_v[i][j] - vase_v[(i + 1) % vase_NBROT][j]);
             vntmp = cross(a, b); // Produit vectoriel =

             // On répercute cette normale sur les 4 sommets de la face
             // (accumulation des normales)
             vase_vn[i][j] = vntmp + vase_vn[i][j];
             vase_vn[(i + 1) % vase_NBROT][j] = vntmp + vase_vn[(i + 1) % vase_NBROT][j];
             vase_vn[(i + 1) % vase_NBROT][j + 1] = vntmp + vase_vn[(i + 1) % vase_NBROT][j + 1];
             vase_vn[i][j + 1] = vntmp + vase_vn[i][j + 1];
         }
     }
     // Normale à un sommet = moyenne de la normale des 4 sommets de la face
     for (int i = 0; i < vase_NBROT; i++) {
         for (int j = 0; j < vase_NBPT; j++) {
             float q = 4.0f;
             if (j == vase_NBPT - 1) // Points du bord
                 q = 2.0f;
             vase_vn[i][j] = vase_vn[i][j] / q;
         }//for_i
     }//for_j
 }







 void ViewerEtudiant::init_vase()
 {
     m_vase = Mesh(GL_TRIANGLES); // Primitive OpenGL
     m_vase.color(1.0, 1.0, 1.0); // Couleur du Mesh
     for (int i = 0; i < vase_NBROT; i++) {
         for (int j = 0; j < vase_NBPT - 1; j++) { // Attention boucle de 0 à vase_NBPT-2 car (j+1)
         // Premier triangle
             m_vase.texcoord(0, 0);
             m_vase.normal(vase_vn[i][j]);
             m_vase.vertex(vase_v[i][j]);

             m_vase.texcoord(1, 1);
             m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j + 1]);
             m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j + 1]);

             m_vase.texcoord(1, 0);
             m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j]);
             m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j]);

             // Second triangle
             m_vase.texcoord(0, 0);
             m_vase.normal(vase_vn[i][j]);
             m_vase.vertex(vase_v[i][j]);

             m_vase.texcoord(0, 1);
             m_vase.normal(vase_vn[i][j + 1]);
             m_vase.vertex(vase_v[i][j + 1]);

             m_vase.texcoord(1, 1);
             m_vase.normal(vase_vn[(i + 1) % vase_NBROT][j + 1]);
             m_vase.vertex(vase_v[(i + 1) % vase_NBROT][j + 1]);
         }//for_j
     }//for_i
 }








 void ViewerEtudiant::init_mongolfiere()
 {
 }





 //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 










 //--------------------------------------------------------------INIT---------------------------------------------------------------------------------------------

 //Fonction dans laquelle les initialisations sont faites.
 
int ViewerEtudiant::init()
{
    Viewer::init();

    
    
    m_camera.lookat( Point(0,0,0), 150 );
   // gl.light(Point(0, 50, 50), White());

     
   

    //----------------------------------Création des Mesh des Formes de base--------------------------------------------------------------------------------------
     // Appel des fonctions init_votreObjet pour creer les Mesh


    init_quad();            
    init_cube();            
    init_cylindre();        
    init_disque();
    init_cone();
    init_sphere();
    //------------------------------------------------------------------------------------------------------------------------------------------------------------

    init_cubemap();
    init_mouette1();
    init_mongolfiere();
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
     // Calcul des coordonnées des sommets et des normales
    create_vertex_normal_vase();

    init_vase();
    


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------



    // Chargement de l’image servant de carte de hauteur
    const Image m_terrainAlti = read_image("../data/terrain/terrain.png");
   



    // Création du Mesh
    init_terrain(m_terrain, m_terrainAlti);
    init_tree(m_terrainAlti);
    



    /// Chargement des textures
    terrain_texture = read_texture(0, "../data/terrain/terrain_texture.png");
    avion_texture = read_texture(0, "../data/avion.jfif");
    tree_texture = read_texture(0, "../data/billboard/arbre.png");
    cubemap_texture = read_texture(0, "../data/cubemap/skybox.png");
    mongolfiere_texture = read_texture(0, "../data/cube-mongo.jpg");
    mongolfiere_texture1 = read_texture(0, "../data/cube-mongo1.jpg");






    //chargement des textures de la mouette :
    mouette1_texture = read_texture(0, "../data/billboard/textanim/1.png");
    mouette2_texture = read_texture(0, "../data/billboard/textanim/2.png");
    mouette3_texture = read_texture(0, "../data/billboard/textanim/3.png");
    mouette4_texture = read_texture(0, "../data/billboard/textanim/4.png");




    
    
    return 0;
}





//----------------------------------------------Définition des procédures draw_monObjet pour les formes de bases--------------------------------------------------------------------------------------- -

void ViewerEtudiant::draw_cube(const Transform& T)
{
    gl.texture(0);
    gl.model(T);
    gl.draw(m_cube);

}



void ViewerEtudiant::draw_cylindre(const Transform& T)
{

    gl.model(T);
    gl.draw(m_cylindre);
    // Disque du haut
    Transform Tch = T * Translation(0, 1, 0) * Rotation(Vector(1, 0, 0), 180);
    gl.model(Tch);
    gl.draw(m_disque);
    // Disque du bas
    Transform Tcb = T * Translation(0, -1, 0);
    gl.model(Tcb);
    gl.draw(m_disque);


}



void ViewerEtudiant::draw_disque(const Transform& T)
{
    gl.model(T);
    gl.draw(m_disque);
}



void ViewerEtudiant::draw_cone(const Transform& T)
{

    gl.model(T);
    gl.draw(m_cone);
    gl.model(T);
    gl.draw(m_disque);

}



void ViewerEtudiant::draw_sphere(const Transform& T)
{
    gl.texture(0);
    gl.model(T);
    gl.draw(m_sphere);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------





//---------------------------------définition de draw_terrain------------------------------------------------------------------------------------------------------
void ViewerEtudiant::draw_terrain(const Transform& T) {

    gl.texture(terrain_texture);
    gl.model(T);
    gl.draw(m_terrain);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------






//--------------------------------------définition de draw_tree---------------------------------------------------------------------------------------------------
void ViewerEtudiant::draw_tree(const Transform& T)
{
    int rotation = 0; //initialise la variable rotation a 0
    

    for (int w = 0; w < 10; w++)
    {
        Transform Tc = T * Translation(TabPosition[w][0], TabPosition[w][1], TabPosition[w][2]) * Translation(-65, 4, -63);
        for (int rotation = 0; rotation <= 375; rotation += 25) // boucle pour faire la rotation qui change de 25 degre a chaque itération
        {
            gl.model(Tc * RotationY(rotation) * Scale(5,5,5)); // applique la rotation a chaque itération
            gl.texture(tree_texture); //applique la texture sur le quad
            gl.draw(m_quad); // affichage
        }
    }

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





//--------------------------------------définition de l'avion(Objet complexe construit en utilisant les formes de bases--------------------------------------------------------------
void ViewerEtudiant::draw_avion(const Transform& T)
{
    
    //---------------------------------------Sphere pour faire la partie principale de l'avion-------------------------------------------------------------------------------------
    Transform A1 = T * Scale(7, 1, 1.5); 
    gl.model(A1);
    gl.texture(avion_texture);
    gl.draw(m_sphere);

    //--------------------------------------Le cone avec ses traansformations géometrique pour faire les ailes de l'avion---------------------------------------------------------------
    Transform A2 = T * RotationX(90) * RotationZ(-90) * Scale(10, 2, 0.3);
    gl.model(A2);
    gl.texture(avion_texture);
    gl.draw(m_cone);
    //--------------------------------------Le disque qui ferme le cone des ailes-------------------------------------------------------------------------------------------------------
    Transform A2A = A2 * Translation(0, 0, 0) * RotationX(0);
    gl.model(A2A);
    gl.draw(m_disque);

    //-----------------------------------------------------------------Les deux cubes etirés qui font la partie postérieure de l'avion-----------------------------------------------------
    Transform A3 = T * Translation(-6, 0, 0) * Scale(0.25, 0.05, 3);
    gl.model(A3);
    gl.texture(avion_texture);
    gl.draw(m_cube);
    Transform A3A = T * Translation(-6, 0.5, 0) * Scale(-0.5, -0.4, 0.05); 
    gl.model(A3A);
    gl.texture(avion_texture);
    gl.draw(m_cube);


    //-----------------------------------------------------------------------Les deux cylindre qui font office de réacteurs de l'avion------------------------------------------------------
    Transform A4A = T * Scale(0.75, 0.75, 0.75) * Translation(0, -1, -10) * RotationZ(90.0);
    gl.model(A4A);
    gl.texture(avion_texture);
    gl.draw(m_cylindre);
    Transform A4B = T * Scale(0.75, 0.75, 0.75) * Translation(0, -1, 10) * RotationZ(90.0);
    gl.model(A4B);
    gl.texture(avion_texture);
    gl.draw(m_cylindre);

    //-----------------------------------------------------------------------Les deux disques qui fermes les deux cylindres de la parties arrière------------------------------------

    Transform A5A = A4A * Translation(0, 1, 0) * RotationX(180);
    gl.model(A5A);
    gl.draw(m_disque);
    Transform A5B = A4B * Translation(0, 1, 0) * RotationX(180);
    gl.model(A5B);
    gl.draw(m_disque);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------




//----------------------------------------définition cde cubemap--------------------------------------------------------------------------------------------------
void  ViewerEtudiant::draw_cubemap(const Transform& T)
{
    gl.texture(cubemap_texture); // Application de la texture du cubemap sur les coordonnées déja definit dans le init
    gl.model(T * Translation(0,81,0) * Scale(62, 75, 63)); //Transformation géometrique necessaire pour aggrandir et bouger le cubemap
    gl.draw(m_cubemap); //L'affichage 
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------





void ViewerEtudiant::draw_mongolfiere(const Transform& T)

{
    

    
    Transform B = T * Translation(15, 40, 0) * Scale(10,5,12);
    gl.texture(mongolfiere_texture1);
    gl.model(B);
    gl.draw(m_vase);

    
    Transform A = T *  Translation(15, 37, 0) * Scale(2, 2, 2);
    gl.texture(mongolfiere_texture);
    gl.model(A);
    gl.draw(m_cube);




}





















//----------------------------------Draw texture mouette----------------------------------------------------------------------------------------------------------


void ViewerEtudiant::draw_mouette1(const Transform& T)
{
    if (compteurTps % 4 == 0) //utilisation d'un modulo qui consiste a faire afficher uen texture differente a chaque itération 
    {
        gl.texture(mouette1_texture);
    }
    else if (compteurTps % 4 == 1)
    {
        gl.texture(mouette2_texture);
    }
    else if (compteurTps % 4 == 2)
    {
        gl.texture(mouette3_texture);
    }
    else if (compteurTps % 4 == 3)
    {
        gl.texture(mouette4_texture);
    }
    
  
   

    gl.model(T);
    gl.draw(m_mouette1);
   
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------Draw_vase--------------------------------------------------------------------------------------------------------------

void ViewerEtudiant::draw_vase(const Transform& T) {
    gl.texture(avion_texture);
    gl.model(T);
    gl.draw(m_vase);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------RENDER-----------------------------------------------------------------------------------------------------------------------
/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    manageCameraLight();
    gl.camera(m_camera);
    
    
    
    
    /// Appel des fonctions du type 'draw_votreObjet'
        
    //Appel de fonctions a désactiver si on veut afficher les formes de bases :
    
    

   // Transform G = Translation(-15, 40, 0); 
   // draw_cube(G);


  //  Transform N = Translation(-11, 40, 0); 
   // draw_cylindre(N);



   // Transform L = Translation(-15, 50, 0);
    //draw_cone(L);



   // Transform J = Translation(-11, 50, 0);
   // draw_sphere(J);


    draw_avion(Tavion * Translation(-10,60,-30));


    

    Transform T = Translation(-65,0,-63);  
    draw_terrain(T);


      





    gl.alpha(0.5f); //utilisation de gl.alpha pour gerer la transparence du carré et le rendre transparent pour voir que la texture plaqué dessus.
    draw_tree(Identity());



    
    //appel de draw cube map pour afficher le cubemap
    draw_cubemap(Identity());


    //appel de draw mouette pour l'afficher
    //Transform S = Translation(-20, 20, 0);
    draw_mouette1(Translation(-10, 30, -45));
    draw_mouette1(Translation(-13, 32, -40));
    draw_mouette1(Translation(-17, 34, -45));
    draw_mouette1(Translation(-21, 30, -38));
    draw_mouette1(Translation(-25, 30, -35));
    draw_mouette1(Translation(-28, 34, -25));

    draw_mouette1(Translation(20, 35, -45));
    draw_mouette1(Translation(20, 40, -35));









    draw_mongolfiere(Tmongolfiere);

    

    return 1;
    
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------






//--------------------------------------------Update---------------------------------------------------------------------------------------------------------------------

/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{


    float temps1 = time / 150;
    int temps2 = int(temps1);

    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.
    
    compteurTps = temps2; // On crée un compteur pour l'utiliser pour les textures animées.




    //TP 6 animation

    
    float ts = time / 300.0;

    int te = int(ts);
    int ite = te % m_anim.nb_points();
    int ite_suiv = (te + 1) % m_anim.nb_points();
    int ite_suiv_suiv = (ite_suiv + 1) % m_anim.nb_points();

    Point p0 = m_anim[ite];
    Point p1 = m_anim[ite_suiv];
    Point p2 = m_anim[ite_suiv_suiv];

    float poids = ts - te;

    Vector pos = Vector(p0) + (Vector(p1) - Vector(p0)) * poids;
    Vector pos_suiv = Vector(p1) + (Vector(p2) - Vector(p1)) * poids;

    Vector dir = normalize(pos_suiv - pos);
    Vector up = Vector(0, 1, 0);
    Vector codir = cross(dir, up);


    Tavion = Transform(dir, up, codir, pos);
    Tmongolfiere = Transform(dir, up, codir, pos);



 


    
    return 0;
}


/*
 * Constructeur.
 */


 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------










//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------











/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}


