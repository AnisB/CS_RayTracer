#include "parser.h"

Scene* Parser::GetSceneFromFile(std::string filename)
{
    Scene* scene = NULL;
    fstream fichierScene(filename.c_str(), ios::in );

    if( fichierScene.is_open() )
    {
        PRINT_GREEN("Fchier de scene bien ouvert.");
        scene = new Scene();
        EtatTraitementScene EtatCourant = TRAITEMENT_SCENE;
        EtatTraitementScene EtatNouveau = TRAITEMENT_SCENE;

        char line[ NB_MAX_CAR_PAR_LIGNE ];
        string buffer;

        Light light;
        Triangle triangle;
        Plan plan;
        Quadrique quadric;
        Materiau materiau;

        float Val0, Val1, Val2;
        float  R, G, B;

        while( !fichierScene.eof() )
        {
            fichierScene.getline( line, NB_MAX_CAR_PAR_LIGNE );
            buffer = line;
            CStringUtils::Trim( buffer, " ");

            // Passer les lignes vides et les commentaires
            if( buffer.empty() || buffer[ 0 ] == '*'  || buffer[ 0 ] == '\r' )
                continue;
            else
            {
                // Vérifier l'arrivée d'un nouvel état de traitement
                bool EstNouvelObjetScene = true;
                if     ( STRING_CHECKFIND( buffer, "Lumiere:" ) ) EtatNouveau = TRAITEMENT_LUMIERE;
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
                            scene->AddLight(light);
                        else
                        {
                            switch(EtatCourant)
                            {
                            case TRAITEMENT_PLAN:
                                scene->AddPlane(plan, materiau);
                                break;
                            case TRAITEMENT_TRIANGLE:
                                scene->AddTriangle(triangle, materiau);
                                break;
                            case TRAITEMENT_QUADRIQUE:
                                scene->AddQuadric(quadric, materiau);
                                break;
                            default:
                                PRINT_RED("Cas non pris en charge.");
                            }
                        }
                    }

                    // Substituer le nouvel état pour l'ancien
                    EtatCourant = EtatNouveau;
                }
                else
                {
                    // Remplir les informations génériques de l'objet courant

                    bool IsGenericsurfaceInfo = true;

                    if( STRING_CHECKFIND( buffer, "color:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &R, &G, &B );
                        materiau.color = Vector4(R, G, B, 1.0f);
                    }
                    /*else if( STRING_CHECKFIND( buffer, "ambient:" ) )
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
                    }*/
                    else if( STRING_CHECKFIND( buffer, "reflect:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                        materiau.coeffReflexion = Val0;
                    }
                    else if( STRING_CHECKFIND( buffer, "refract:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f", line, &Val0, &Val1 );
                        materiau.coeffRefraction = Val0;
                        materiau.indiceRefraction = Val1;
                    }/*
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
                    }*/
                    else
                        IsGenericsurfaceInfo = false;

                    if( IsGenericsurfaceInfo )
                        continue;
                }

                // Remplir les infos spécifiques à l'objet
                switch( EtatCourant )
                {
                case TRAITEMENT_SCENE:

                    /*if( STRING_CHECKFIND( buffer, "background:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %i %i %i", line, &R, &G, &B );
                        AjusterCouleurArrierePlan( CCouleur( R, G, B ) );
                    }
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
                        light.position = Vector3(Val0, Val1, Val2);
                    }
                    else if( STRING_CHECKFIND( buffer, "intens:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                        light.intensity = Val0;
                    }
                    else if( STRING_CHECKFIND( buffer, "colorSpec:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &R, &G, &B );
                        light.color = Vector3(R, G, B);
                    }

                    break;

                case TRAITEMENT_TRIANGLE:

                    if( STRING_CHECKFIND( buffer, "point:" ) )
                    {
                        int PtIdx;
                        sscanf( buffer.c_str(), "%s %i %f %f %f", line, &PtIdx, &Val0, &Val1, &Val2 );
                        switch(PtIdx)
                        {
                            case 0:
                            triangle.p0 = Vector3(Val0, Val1, Val2);
                            break;
                            case 1:
                            triangle.p1 = Vector3(Val0, Val1, Val2);
                            break;
                            case 2:
                            triangle.p2 = Vector3(Val0, Val1, Val2);
                            triangle.normale = Vector3::crossProduct(triangle.p1-triangle.p0,triangle.p2-triangle.p0);
                            triangle.normale = triangle.normale/triangle.normale.Norm();
                            break;
                        }
                    }

                    break;

                case TRAITEMENT_PLAN:

                    if( STRING_CHECKFIND( buffer, "v_linear:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                        //( ( CPlan* )surface )->AjusterNormale( CVecteur3( Val0, Val1, Val2 ) );
                    }
                    else if( STRING_CHECKFIND( buffer, "v_const:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                        //( ( CPlan* )surface )->AjusterConstante( Val0 );
                    }

                    break;

                case TRAITEMENT_QUADRIQUE:

                    if( STRING_CHECKFIND( buffer, "v_quad:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                        quadric.A = Val0;
                        quadric.B = Val1;
                        quadric.C = Val2;
                    }
                    else if( STRING_CHECKFIND( buffer, "v_mixte:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                        quadric.D = Val0;
                        quadric.E = Val1;
                        quadric.F = Val2;
                    }
                    else if( STRING_CHECKFIND( buffer, "v_linear:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f %f %f", line, &Val0, &Val1, &Val2 );
                        quadric.G = Val0;
                        quadric.H = Val1;
                        quadric.I = Val2;
                    }
                    else if( STRING_CHECKFIND( buffer, "v_const:" ) )
                    {
                        sscanf( buffer.c_str(), "%s %f", line, &Val0 );
                        quadric.J = Val0;
                    }
                    break;
                default:
                    PRINT_RED("Cas non pris en charge.");
                }
            }
        }

        // Fermer le fichier de scène
        fichierScene.close();

        // Ajouter le dernier objet traité
        switch(EtatCourant)
        {
        case TRAITEMENT_PLAN:
            scene->AddPlane(plan, materiau);
            break;
        case TRAITEMENT_TRIANGLE:
            scene->AddTriangle(triangle, materiau);
            break;
        case TRAITEMENT_QUADRIQUE:
            scene->AddQuadric(quadric, materiau);
            break;
        case TRAITEMENT_LUMIERE:
            scene->AddLight(light);
            break;
        default:
            PRINT_RED("Cas non pris en charge.");
        }
    }
    else
        PRINT_RED("[Parser::GetSceneFromFile()] : Incapable d'ouvrir " << filename);

    return scene;
}
