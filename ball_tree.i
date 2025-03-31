%module ball_tree
%{
#include "ball_tree.h"
%}

%include "std_vector.i"
%template(VectorDouble) std::vector<double>;
%template(VectorVectorDouble) std::vector<std::vector<double>>;

%include "ball_tree.h"

// Exponer la clase BallTree a Python
%feature("director") BallTree;
