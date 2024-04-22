#include <fstream>

void read_input(string filename, Mesh* M){
    string line;
    float k, Q, T_bar, T_hat;
    int num_nodes, num_elements, num_dirichlet, num_neumann;
    ifstream dat_file(filename+".dat");

    dat_file >> k >> Q >> T_bar >> T_hat >> num_nodes >> num_elements >> num_dirichlet >> num_neumann;
    
    M->set_problem_data(k,Q);
    M->set_quantities(num_nodes,num_elements,num_dirichlet,num_neumann);

    M->init_arrays();

    dat_file >> line;

    for(int i = 0; i < num_nodes; i++){
        int id;
        float x;
        dat_file >> id >> x;
        M->insert_node(new Node(id,x), i);
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_elements; i++){
        int id, node1_id, node2_id;
        dat_file >> id >> node1_id >> node2_id;
        M->insert_element( new Element(id, M->get_node(node1_id-1), M->get_node(node2_id-1)) , i);
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_dirichlet; i++){
        int id;
        dat_file >> id;
        M->insert_dirichlet_condition(new Condition(M->get_node(id-1), T_bar), i);
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_neumann; i++){
        int id;
        dat_file >> id;
        M->insert_neumann_condition(new Condition(M->get_node(id-1), T_hat), i);
    }

    dat_file.close();
}
