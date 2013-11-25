#include "Parser.h"

Parser::Parser()
{
    
}

Parser::~Parser()
{
    
}

void Parser::AddSurface( ISurface* const surface )
{
    m_surfaces.push_back( surface );
}

void Parser::AddLight( CLumiere* const light )
{
    m_lights.push_back( light );
}

Scene* Parser::GetSceneFromFile(std::string filename)
{
    Scene* scene;
    fstream fichierScene(filename.c_str(), ios::in );

    if( fichierScene.is_open() )
    {
        EtatTraitementScene EtatCourant = TRAITEMENT_SCENE;
        EtatTraitementScene EtatNouveau = TRAITEMENT_SCENE;

        char line[ NB_MAX_CAR_PAR_LIGNE ];
        string buffer;
        int count = 0;

        CLumiere* light = NULL;
        ISurface* surface = NULL;

        float Val0, Val1, Val2;
        int  R, G, B;

        while( !fichierScene.eof() )
        {
            fichierScene.getline( line, NB_MAX_CAR_PAR_LIGNE );
            buffer = line;
            CStringUtils::Trim( buffer, " " );

            // Passer les lignes vides et les commentaires
            if( buffer.empty() || buffer[ 0 ] == '*' )
                continue;
            else
            {
                // Vérifier l'arrivée d'un nouvel état de traitement
                bool EstNouvelObjetScene = true;
                if     ( STRING_CHECKFIND( buffer, "light:" ) ) EtatNouveau = TRAITEMENT_LUMIERE;
                else if( STRING_CHECKFIND( buffer, "Poly:"    ) ) EtatNouveau = TRAITEMENT_TRIANGLE;
                else if( STRING_CHECKFIND( buffer, "Plane:"   ) ) EtatNouveau = TRAITEMENT_PLAN;
                else if( STRING_CHECKFIND( buffer, "Quad:"    ) ) EtatNouveau = TRAITEMENT_QUADRIQUE;
                else
                    EstNouvelObjetScene = false;

                if( EstNouvelObjetScene )
                {
                    // Ajouter objet nouvellement traité à la scène
                    if( EtatCourant != TRAITEMENT_SCENE )
                    {
                        if( EtatCourant == TRAITEMENT_LUMIERE ) 
                            AddLight( light );
                        else        
                            AddSurface( surface );

                        surface = NULL;
                        light = NULL;
                    }

                    // Substituer le nouvel état pour l'ancien
                    EtatCourant = EtatNouveau;

                    // créer un nouvel objet de scène puis le remplir
                    switch( EtatCourant )
                    {
                    case TRAITEMENT_LUMIERE:
                        light = new CLumiere();
                        cout << "[ACTION]: Creation d'une lumiere..." << endl;
                        break;
                    case TRAITEMENT_TRIANGLE:
                        surface = new CTriangle();
                        cout << "[ACTION]: Creation d'un triangle..." << endl;
                        break;
                    case TRAITEMENT_PLAN:
                        surface = new CPlan();
                        cout << "[ACTION]: Creation d'un plan..." << endl;
                        break;
                    case TRAITEMENT_QUADRIQUE:
                        surface = new CQuadrique();
                        cout << "[ACTION]: Creation d'une quadrique..." << endl;
                        break;
                    }
                }
                else
                {
                    // Remplir les informations génériques de l'objet courant
                    if( surface != NULL )
                    {
                        bool IsGenericsurfaceInfo = true;

                        if( STRING_CHECKFIND( buffer, "color:" ) )
                        { 
                            sscanf( buffer.c_str(), "%s %i %i %i", line, &R, &G, &B );
                            surface->AjusterCouleur( CCouleur( R, G, B ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "ambient:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            surface->AjusterCoeffAmbiant( Val0 );
                        }
                        else if( STRING_CHECKFIND( buffer, "diffus:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            surface->AjusterCoeffDiffus( Val0 );
                        }
                        else if( STRING_CHECKFIND( buffer, "specular:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f", line, &Val0, &Val1 );
                            surface->AjusterCoeffSpeculaire( Val0 );
                            surface->AjusterCoeffBrillance( Val1 );
                        }
                        else if( STRING_CHECKFIND( buffer, "reflect:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            surface->AjusterCoeffReflexion( Val0 );
                        }
                        else if( STRING_CHECKFIND( buffer, "refract:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f", line, &Val0, &Val1 );
                            surface->AjusterCoeffRefraction( Val0 );
                            surface->AjusterIndiceRefraction( Val1 );
                        }
                        else if( STRING_CHECKFIND( buffer, "rotate:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );

                            CMatrice4 Transform = surface->ObtenirTransformation();
                            Transform.RotationAutourDesX( Deg2Rad<REAL>( Val0 ) );
                            Transform.RotationAutourDesY( Deg2Rad<REAL>( Val1 ) );
                            Transform.RotationAutourDesZ( Deg2Rad<REAL>( Val2 ) );
                            surface->AjusterTransformation( Transform );
                        }
                        else if( STRING_CHECKFIND( buffer, "translate:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            CMatrice4 Transform = surface->ObtenirTransformation();
                            Transform.Translation( Val0, Val1, Val2 );
                            surface->AjusterTransformation( Transform );
                        }
                        else if( STRING_CHECKFIND( buffer, "scale:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            CMatrice4 Transform = surface->ObtenirTransformation();
                            Transform.MiseAEchelle( Val0, Val1, Val2 );
                            surface->AjusterTransformation( Transform );
                        }
                        else
                            IsGenericsurfaceInfo = false;

                        if( IsGenericsurfaceInfo )
                            continue;
                    }

                    // Remplir les infos spécifiques à l'objet
                    switch( EtatCourant )
                    {
                    case TRAITEMENT_SCENE:

                        if( STRING_CHECKFIND( buffer, "background:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %i %i %i", line, &R, &G, &B );
                            AjusterCouleurArrierePlan( CCouleur( R, G, B ) );
                        }
/*
                        else if( STRING_CHECKFIND( buffer, "origin:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            AjusterPositionCamera( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "eye:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            AjusterPointViseCamera( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "up:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            AjusterVecteurUpCamera( CVecteur3( Val0, Val1, Val2 ) );
                        }
*/


                        break;

                    case TRAITEMENT_LUMIERE:

                        if( STRING_CHECKFIND( buffer, "position:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            light->SetPosition( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "intens:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            light->SetIntensity( Val0 );
                        }
                        else if( STRING_CHECKFIND( buffer, "color:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %i %i %i", line, &R, &G, &B );
                            light->AjusterCouleur( CCouleur( R, G, B ) );    
                        }

                        break;

                    case TRAITEMENT_TRIANGLE:

                        if( STRING_CHECKFIND( buffer, "point:" ) )
                        {
                            int PtIdx;
                            sscanf( buffer.c_str(), "%s %i %f %f %f", line, &PtIdx, &Val0, &Val1, &Val2 );
                            ( ( CTriangle* )surface )->AjusterPoint( PtIdx, CVecteur3( Val0, Val1, Val2 ) );
                        }

                        break;

                    case TRAITEMENT_PLAN:

                        if( STRING_CHECKFIND( buffer, "v_linear:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            ( ( CPlan* )surface )->AjusterNormale( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "v_const:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            ( ( CPlan* )surface )->AjusterConstante( Val0 );
                        }

                        break;

                    case TRAITEMENT_QUADRIQUE:

                        if( STRING_CHECKFIND( buffer, "v_quad:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            ( ( CQuadrique* )surface )->AjusterQuadratique( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "v_mixte:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            ( ( CQuadrique* )surface )->AjusterMixte( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "v_linear:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                            ( ( CQuadrique* )surface )->AjusterLineaire( CVecteur3( Val0, Val1, Val2 ) );
                        }
                        else if( STRING_CHECKFIND( buffer, "v_const:" ) )
                        {
                            sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                            ( ( CQuadrique* )surface )->AjusterConstante( Val0 );
                        }

                        break;
                    }
                }
            }
        }

        // Fermer le fichier de scène
        fichierScene.close();

        // Ajouter le dernier objet traité
        if( surface != NULL ) AddSurface( surface );
        if( light != NULL ) AddLight( light );
    }
    else
        cerr << "[CScene::TraiterFichierDeScene()] : Incapable d'ouvrir " << filename << "." << endl;

    return scene;
}

void Parser::AjusterCouleurArrierePlan( const CCouleur& Couleur )
{
    m_CouleurArrierePlan = Couleur;
}
