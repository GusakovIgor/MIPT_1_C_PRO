#include "Diff.h"

//
void Dissertation (Tree* tree)
{
    static int call = 666;
    FILE* LaTeX = fopen ("LaTeX\\LaTeX_expression.latex", "w");
    
    PrintHeader (LaTeX);
    
    fprintf (LaTeX, "\\begin{document}\n");
    
    Tree* diff_tree = TreeConstruct (diff_tree);
    diff_tree->root = Differentiate (tree->root);
    MakeParents (diff_tree->root);
    
    
    fprintf (LaTeX, "\\\\ Вот такую штучку нам придётся упрощать: \\\\");
    
    PrintNode (diff_tree->root, LaTeX);
    
    diff_tree->home = LaTeX;
    diff_tree->root = SimplifyNode (diff_tree, diff_tree->root);
    
    fprintf (LaTeX, "А вот мы и добрались до финала: \\\\");
    PrintNode (diff_tree->root, LaTeX);
    
    fprintf (LaTeX, "\\end{document}");
    
    fclose (LaTeX);
    
    CompileLaTeX (call);
    
    call++;
}
//

void FormulaPrint (Tree* tree)
{
    static int call = 0;
    FILE* LaTeX = fopen ("LaTeX\\LaTeX_expression.latex", "w");
    
    PrintHeader (LaTeX);
    
    fprintf (LaTeX, "\\begin{document}\n");
    fprintf (LaTeX, "\\[ ");
    PrintNode (tree->root, LaTeX);
    fprintf (LaTeX, " \\]\n");
    fprintf (LaTeX, "\\end{document}");
    
    fclose (LaTeX);
    
    CompileLaTeX (call);
    
    call++;
}

void CompileLaTeX (int call)
{
    char command_1 [MAX_COMMAND_LEN] = "";
    char command_2 [MAX_COMMAND_LEN] = "";
    
    sprintf (command_1, "pdflatex --output-directory=./LaTeX --output-format=pdf --jobname LaTeX_expression_%d ./LaTeX/LaTeX_expression.latex", call);
    sprintf (command_2, "start LaTeX\\LaTeX_expression_%d.pdf", call);
    
    system (command_1);
    system (command_2);
}

void PrintHeader (FILE* LaTeX)
{
    fprintf (LaTeX, "\\documentclass[a4paper,12pt]{article}\n");
    fprintf (LaTeX, "\\usepackage[T2A]{fontenc}\n");
    fprintf (LaTeX, "\\usepackage[cp1251]{inputenc}\n");
    fprintf (LaTeX, "\\usepackage[english,russian]{babel}\n\n");
    fprintf (LaTeX, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
}

void PrintNode (Node* node, FILE* LaTeX)
{
    switch (node->type)
    {
        case (TYPE_CONST):  fprintf (LaTeX, "%s" , ConstantName(node->value.dbl_val));
                            break;
        
        case (TYPE_NUM):    if (node->value.dbl_val < 0.0)
                                fprintf (LaTeX, "\\left(");
                            fprintf (LaTeX, "%lg", node->value);
                            if (node->value.dbl_val < 0.0)
                                fprintf (LaTeX, "\\right)");
                            break;
                            
        case (TYPE_OP):     PrintOperation (node, LaTeX);
                            break;
        
        case (TYPE_VAR):    fprintf (LaTeX, "%s",  node->value);
                            break;
        
        case (TYPE_FUNC):   fprintf (LaTeX, "\\%s", FunctionName (node->value.int_val));
                            if (node->parent && node->parent->type == TYPE_OP && node->parent->value.int_val == OP_DEG)
                            {
                                PrintSign (OP_DEG, LaTeX);
                                PrintSubNode (node->parent->right, LaTeX, OP_DEG);
                            }
                            PrintFuncArg (node, LaTeX);
                            break;
    }
}

void PrintOperation (Node* node, FILE* LaTeX)
{
    int operation = node->value.int_val;
    
    if (operation == OP_DIV)
    {
        PrintSign (operation, LaTeX);
        PrintSubNode (node->left,  LaTeX, operation);
        PrintSubNode (node->right, LaTeX, operation);
    }
    else if (operation == OP_DEG && node->left->type == TYPE_FUNC)
    {
        PrintSubNode (node->left,  LaTeX, operation);
    }
    else
    {
        PrintSubNode (node->left,  LaTeX, operation);
        PrintSign (operation, LaTeX);
        PrintSubNode (node->right, LaTeX, operation);
    }
}

void PrintSubNode (Node* sub_node, FILE* LaTeX, int operation)
{
    fprintf (LaTeX, "{");
    if (sub_node->type == TYPE_OP && (operation - sub_node->value.int_val >= 2 || (operation == OP_SUB && sub_node == sub_node->parent->right && sub_node->value.int_val == OP_ADD)))
        fprintf (LaTeX, "\\left(");
    
    PrintNode (sub_node,  LaTeX);
    
    if (sub_node->type == TYPE_OP && (operation - sub_node->value.int_val >= 2 || (operation == OP_SUB && sub_node == sub_node->parent->right && sub_node->value.int_val == OP_ADD)))
        fprintf (LaTeX, "\\right)");
    fprintf (LaTeX, "}");
}

void PrintSign (int operation, FILE* LaTeX)
{
    switch (operation)
    {
        case (OP_ADD):      fprintf (LaTeX, " + ");
                            break;
        
        case (OP_SUB):      fprintf (LaTeX, " - ");
                            break;
        
        case (OP_MUL):      fprintf (LaTeX, " \\cdot ");
                            break;
        
        case (OP_DIV):      fprintf (LaTeX, " \\frac ");
                            break;
        
        case (OP_DEG):      fprintf (LaTeX, " ^ ");
                            break;
    }
}

void PrintFuncArg (Node* node, FILE* LaTeX)
{
    fprintf (LaTeX, "\\left(");
    PrintNode (node->right, LaTeX);
    fprintf (LaTeX, "\\right)");
}
