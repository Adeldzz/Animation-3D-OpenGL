
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"



class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update( const float time, const float delta );
    int compteurTps = 0;

protected:
    
    float TabPosition[10][3];
        
    


        
        
    
    /// Declaration des Mesh
        Mesh m_quad;
        Mesh m_cube;
        Mesh m_cylindre;
        Mesh m_cone;
        Mesh m_sphere;
        Mesh m_disque;

        Mesh m_terrain; // Déclaré dans ViewerEtudiant
        Mesh m_cubemap;

        Mesh m_mouette1;

        Mesh m_vase;
       

    /// Declaration des Textures
        GLuint avion_texture; // Texture avec image 
        GLuint terrain_texture;
        GLuint tree_texture;
        GLuint cubemap_texture;
        GLuint mongolfiere_texture;
        GLuint mongolfiere_texture1;


     //Texture mouette:
        GLuint mouette1_texture;
        GLuint mouette2_texture;
        GLuint mouette3_texture;
        GLuint mouette4_texture;
        GLuint mouette5_texture;

    
    /// Declaration des fonction de creation de Mesh du type init_votreObjet()
      void init_quad();
      void init_cube(); 
      void init_cylindre();
      void init_disque();
      void init_cone();
      void init_sphere();
      void init_tree(const Image& im);
      void init_terrain(Mesh& m_terrain, const Image& im);
      void init_cubemap();


      void init_avion();
      Transform Tavion; 
      


      void init_mouette1();

      void init_vase();

      void init_mongolfiere();
      Transform Tmongolfiere;



    


      
    /// Declaration des fonctions draw_votreObjet(const Transform& T)

      void draw_quad(const Transform& T);
      void draw_cube(const Transform& T);
      void draw_cylindre(const Transform& T);
      void draw_disque(const Transform& T);
      void draw_cone(const Transform& T);
      void draw_sphere(const Transform& T);
      void draw_avion(const Transform& T);
      void draw_tree(const Transform& T);
      void draw_terrain(const Transform& T);
      void draw_cubemap(const Transform& T);


      void draw_mouette1(const Transform& T);


      void draw_mongolfiere(const Transform& T);


      //fonction nécéssaire a la création d'un vase

      void create_vertex_normal_vase();
      void draw_vase(const Transform& T);



      //création d'un objet par extrusion

      int vase_NBPT;
      Point vase_p[10];
      int vase_NBROT;
      Point vase_v[20][10];
      Vector vase_vn[20][10];





      
      

         
};



#endif

