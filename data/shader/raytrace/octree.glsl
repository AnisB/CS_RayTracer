/* 
 * Code selon l'algorithme de l'article “An Efficient Parametric Algorithm for Octree Traversal”, J. Revelles , C. Ureña , M. Lastra, Journal of WSCG, p. 212-219, 2000 http://wscg.zcu.cz/wscg2000/Papers_2000/X31.pdf
 * passé en itératif
 * La fonction new_node est prise sur l'implementation de Jeroen Baert de l'algorithme en c++ (5 lignes)


*/
int a; // utile pour la traversee de l'octree


#define OCTREE_ACTIVE false

float NODE_STRIDE = 14.0 + NB_PRIM_MAX; // taille prise pour stocker chaque noeud

struct Node {
	int[8]	child_id; // int
	float[6]	coords;  // xmin,ymin,zmin,xmax,ymax,zmax
	int[NB_PRIM_MAX] objects_id; //

};

int stack_id[NB_NOEUD]; // pile pour l'algorithme recursif 
int stackcounter; // index de la pile
Node nodes[NB_NOEUD]; // pile pour l'algorithme recursif
bool nodes_loaded = false;


Node[NB_NOEUD] loadNodes()
{
	Node local_nodes[NB_NOEUD];
	float maxx = NODE_STRIDE-1.0;
	float maxy = NB_NOEUD-1.0;
	for (int i=0;i<NB_NOEUD;i++) {
		float y = (float(i)/NB_NOEUD);
		
		// childs (int)
		local_nodes[i].child_id[0] = int(round(texture(listNoeuds, vec2(0.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[1] = int(round(texture(listNoeuds, vec2(1.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[2] = int(round(texture(listNoeuds, vec2(2.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[3] = int(round(texture(listNoeuds, vec2(3.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[4] = int(round(texture(listNoeuds, vec2(4.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[5] = int(round(texture(listNoeuds, vec2(5.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[6] = int(round(texture(listNoeuds, vec2(6.0/maxx,y)).r *float(NB_NOEUD-1))-1);
		local_nodes[i].child_id[7] = int(round(texture(listNoeuds, vec2(7.0/maxx,y)).r *float(NB_NOEUD-1))-1);


		// coords (float)
		local_nodes[i].coords[0] = texture(listNoeuds, vec2(8.0/maxx,y)).r;
		local_nodes[i].coords[1] = texture(listNoeuds, vec2(9.0/maxx,y)).r;
		local_nodes[i].coords[2] = texture(listNoeuds, vec2(10.0/maxx,y)).r;
		local_nodes[i].coords[3] = texture(listNoeuds, vec2(11.0/maxx,y)).r;
		local_nodes[i].coords[4] = texture(listNoeuds, vec2(12.0/maxx,y)).r;
		local_nodes[i].coords[5] = texture(listNoeuds, vec2(13.0/maxx,y)).r;

		
		// objects_ids (int)
		for (int j=0;j<NB_PRIM_MAX;j++){
			local_nodes[i].objects_id[j] = int(round(texture(listNoeuds, vec2((14.0+j)/maxx,y)).r *float(NB_PRIM-1))-1); // round au lieu de int a cause des erreurs darrondi
		}
	}
    nodes_loaded = true;
    return local_nodes;
}

int[NB_PRIM]  proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, int node_id);




// ------------------------------------
// void ray_parameter (OCTREE) - permet de lancer la traversee de l'octree, avec le rayon passé en parametre. (generalisation pour tous les rayons qqsoit la direction, cf. article)
// ------------------------------------

int[NB_PRIM] ray_paramter ( Ray ray){
	a = 0;
	if (!nodes_loaded) {nodes = loadNodes();}
	
	Node octree = nodes[0];
	float sizeX = octree.coords[3] - octree.coords[0];
	float sizeY = octree.coords[4] - octree.coords[1];
	float sizeZ = octree.coords[5] - octree.coords[2];

	// GENERALISING FOR RAYS WITH NEGATIVE DIRECTIONS
	if (ray.direction[0]<0.0){
		ray.origin[0] = sizeX-ray.origin[0];
		ray.direction[0] = -ray.direction[0];
		a |= 4;
	}
	if (ray.direction[1]<0.0){
		ray.origin[1] = sizeY-ray.origin[1];
		ray.direction[1] = -ray.direction[1];
		a |= 2;
	}
	if (ray.direction[2]<0.0){
		ray.origin[2] = sizeZ-ray.origin[2];
		ray.direction[2] = -ray.direction[2];
		a |= 1;
	}
	 
	double tx0 = (octree.coords[0] - ray.origin[0]) * ray.direction[0];
	double tx1 = (octree.coords[3] - ray.origin[0]) * ray.direction[0];
	double ty0 = (octree.coords[1] - ray.origin[1]) * ray.direction[1];
	double ty1 = (octree.coords[4] - ray.origin[1]) * ray.direction[1];
	double tz0 = (octree.coords[2] - ray.origin[2]) * ray.direction[2];
	double tz1 = (octree.coords[5] - ray.origin[2]) * ray.direction[2];
	
	if( max(max(tx0,ty0),tz0) < min(min(tx1,ty1),tz1) ){
		
		return proc_subtree(tx0,ty0,tz0,tx1,ty1,tz1,0);
	}
}

// ------------------------------------
// int first_node (OCTREE) -- retourne le premier noeud a intersecter (0 a 7)
// ------------------------------------	

uint first_node(double tx0, double ty0, double tz0, double txm, double tym, double tzm){
	int answer = 0;	// 00000000
	double maximum = max(max(tx0,ty0),tz0);

	if(maximum == tx0){ // PLANE YZ
		if(tym < tx0) answer|=2;	// set bit at position 1
		if(tzm < tx0) answer|=1;	// set bit at position 0 			
		return answer; 		
	} 

	if(maximum == ty0){ // PLANE XZ
		if(txm < ty0) answer|=4;	// set bit at position 2
		if(tzm < ty0) answer|=1;	// set bit at position 0			
		return answer; 		
	} 
	
	if(maximum == tz0){ // PLANE XY
		if(txm < tz0) answer|=4;	// set bit at position 2
		if(tym < tz0) answer|=2;	// set bit at position 1
		return answer;	
	}
}


// ------------------------------------
// uint new_node (OCTREE) -- utilise pour la traversee de l'octree (savoir quel est le noeud suivant)
// ------------------------------------	

uint new_node(double txm, int x, double tym, int y, double tzm, int z){
	if(txm < tym){
		if(txm < tzm){return x;}  // YZ plane
	}
	else{
		if(tym < tzm){return y;} // XZ plane
	}
	return z; // XY plane;
}


// ------------------------------------
// void proc_subtree (OCTREE) - traversee de l'octree en iteratif
// ------------------------------------

int[NB_PRIM] proc_subtree (double tx0, double ty0, double tz0, double tx1, double ty1, double tz1, int node_id)
{

	double txm, tym, tzm;
	uint currNode;
	int listePrim[NB_PRIM];
	// init de listePrim
	for (int i =0;i<NB_PRIM;i++){
		listePrim[i]=-1;
	}
 	// init de la pile (empty stack)
	for (int i =0;i<NB_NOEUD;i++){
		stack_id[i]=-1;
	}
	stackcounter = 0;
	stack_id[stackcounter] = node_id; // root
	
	while ( stackcounter != -1 ){ // tant que la pile nest pas vide
		
		
		Node node = nodes[stack_id[stackcounter]]; stackcounter--; // Pop stack

		if(tx1 < 0.0 || ty1 < 0.0 || tz1 < 0.0) continue; // continue (return en recursif)

		if(node.child_id[0] == -1){ // noeud terminal
			
			// ajouter les primitives a la liste des primitives
			for(int i =0;i<NB_PRIM_MAX;i++){
				if (node.objects_id[i] !=-1){
					listePrim[node.objects_id[i]]=1; // mettre 1 a chaque index de listePrim quand la primitive est potentiellement traversee
				}
			}
			continue; // continue (return en recursif)
		}

		// points milieu
		txm = 0.5*(node.coords[0] + node.coords[3]);
		tym = 0.5*(node.coords[1] + node.coords[4]);
		tzm = 0.5*(node.coords[2] + node.coords[5]);
		
		
		currNode = first_node(node.coords[0],node.coords[1],node.coords[2],txm,tym,tzm);

		do{ 		
			switch (currNode) 	{
			case 0: {  			
				stackcounter++;stack_id[stackcounter] = node.child_id[a];
				currNode = new_node(txm,4,tym,2,tzm,1);
				break;}
			case 1: {
				stackcounter++;stack_id[stackcounter] = node.child_id[1^a];
				currNode = new_node(txm,5,tym,3,tz1,8);
				break;}
			case 2: {
				stackcounter++;stack_id[stackcounter] = node.child_id[2^a];
				//proc_subtree(tx0,tym,tz0,txm,ty1,tzm,nodes[node_id].child[2^a]);
				currNode = new_node(txm,6,ty1,8,tzm,3);
				break;}
			case 3: {
				stackcounter++;stack_id[stackcounter] = node.child_id[3^a];
				//proc_subtree(tx0,tym,tzm,txm,ty1,tz1,nodes[node_id].child[3^a]);
				currNode = new_node(txm,7,ty1,8,tz1,8);
				break;}
			case 4: {
				stackcounter++;stack_id[stackcounter] = node.child_id[4^a];
				//proc_subtree(txm,ty0,tz0,tx1,tym,tzm,nodes[node_id].child[4^a]);
				currNode = new_node(tx1,8,tym,6,tzm,5);
				break;}
			case 5: {
				stackcounter++;stack_id[stackcounter] = node.child_id[5^a];
				//proc_subtree(txm,ty0,tzm,tx1,tym,tz1,nodes[node_id].child[5^a]);
				currNode = new_node(tx1,8,tym,7,tz1,8);
				break;}
			case 6: {
				stackcounter++;stack_id[stackcounter] = node.child_id[6^a];
				//proc_subtree(txm,tym,tz0,tx1,ty1,tzm,nodes[node_id].child[6^a]);
				currNode = new_node(tx1,8,ty1,8,tzm,7);
				break;}
			case 7: {
				stackcounter++;stack_id[stackcounter] = node.child_id[7^a];
				//proc_subtree(txm,tym,tzm,tx1,ty1,tz1,nodes[node_id].child[7^a]);
				currNode = 8;
				break;}
			}
		} while (currNode<8);
	
	}
	return listePrim;
}

// Retourne la liste des primitives a tester pour l'intersection
int[NB_PRIM] getPrimitives(Ray parRay)
{
	int listePrims[NB_PRIM];

     if (OCTREE_ACTIVE){
		listePrims = ray_paramter(parRay);
	}
	else {
		for(int i = 0; i < NB_PRIM; i++){
			//listePrims[i] = i;
			listePrims[i] = 1;
		}
	}
	return  listePrims;
}
