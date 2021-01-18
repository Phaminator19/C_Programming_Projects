#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item_node_struct
{
  char name[32];
  int count; 
  struct item_node_struct *left;
  struct item_node_struct *right;
};

typedef struct item_node_struct item_node;

struct tree_name_node_struct {
  char treeName[32];
  struct tree_name_node_struct *left;
  struct tree_name_node_struct *right;
  item_node *theTree;
};

typedef struct tree_name_node_struct tree_name_node;

//create new tree node
tree_name_node *new_tree_node (char *name)
{
  tree_name_node *t = malloc(sizeof(tree_name_node));
  
  t->left = NULL;
  t->right = NULL;
  
  strcpy(t->treeName, name);

  return t;
}
//create new item node
item_node *new_item_node (char *item_name, int count)
{
  item_node *it = malloc(sizeof(item_node));

  strcpy(it->name, item_name);

  it->count = count;
  it->left = NULL;
  it->right = NULL;

  return it;
}

//this function is used as a variable to accept the address of the node I want to delete in the delete_item_in_tree function;
item_node *FindMin(item_node* item)
{
 while(item->left != NULL)
 {
   item = item->left;
 }
 return item;
}

//search for the tree node  "top half" matches
tree_name_node *search_for_name_node (tree_name_node *root, char *treeName)
{
  if (root == NULL)
  {
    return NULL;
  }

  int ret = strcmp(treeName, root->treeName);
  if (ret < 0) {
    return search_for_name_node(root->left, treeName);
  } 

  else if (ret > 0) {
    return search_for_name_node(root->right, treeName);
  }

  else {
    return root;
  }


}

//set child to the left
void set_left_child_tree (tree_name_node *root, item_node *child) 
{
 root->theTree->left = child;
}

//set child to the right
void set_right_child_tree (tree_name_node *root, item_node *child) 
{
  root->theTree->right = child;
}

//set child to the left
void set_left_child_item (item_node *parent, item_node *child) {
  parent->left = child;
}

//set child to the right
void set_right_child_item (item_node *parent, item_node *child) {
  parent->right = child;
}

//delete tree
void delete_tree (tree_name_node *root)
{
  if (root == NULL)
  {
    return;
  }

  free(root);
  root = NULL;
}

//delete_item_in_tree tree in the 
item_node *delete_item_in_tree(tree_name_node *root,item_node *item, char *itemName)
{
  int ret = strcmp(itemName, item->name);

  if (item == NULL)
  {
    return NULL;
  }

  else if (ret < 0) {
    item->left = delete_item_in_tree(root, item->left, itemName);
  }

  else if (ret > 0)
  {
    item->right =  delete_item_in_tree(root, item->right,itemName);
  }

  else 
  {
    //case that has no child
    if (item->left == NULL && item->right == NULL)
    {
      free(item);
      item = NULL;
    }

    //another case that has 1 child
    else if (item->left == NULL)
    {
      item_node *temp = item;

      item = item->right;

      free(temp);
    }
    else if (item->right == NULL)
    {
      item_node *temp = item;

      item = item->left;
      
      free(temp);
    }
    //third case if node has 2 children
    else {
      item_node *temp = item->right;

      strcpy(item->name, temp->name);

      item->right = delete_item_in_tree(root,item->right, temp->name);
    }
  }
return item;
}

//command to check the item before the wanted node
int item_before (item_node *key, char *itemName, int item_count) 
{
   int result = 1;

   if (key != NULL)
   {
     if (strcmp(itemName, key->name) == 0)
     {
      result += item_count +1;
     }
    else if (strcmp(itemName, key->name) < 0)
    {
      result += item_before(key->left, itemName, item_count);
    }
    else {
      result += item_before(key->right, itemName, item_count);
    }
   }
   else {
     return 0;
   }
   return result;
}

//add up all the count data
int count (item_node *item) 
{
int result;

if (item != NULL)
{
  result = item->count + count(item->left) + count(item->right);
}

else {
  return 0;
}

return result;
}

//find the height of the tree
int height_balance (item_node *item) 
{
  if (item == NULL) {
    return -1;
  }
  int left = height_balance(item->left);
  int right = height_balance(item->right);

  if (left > right) {
    return left + 1;
  }
  else 
  {
    return right + 1;
  }
}

//search for the "bottom half" subtree
item_node *search_in_name_node(item_node *item, tree_name_node *root, char *itemName)
{
  if (root == NULL) 
  {
    return NULL;
  }

  else if (item == NULL){
    return NULL;
  }
  
  int ret = strcmp(itemName, item->name);

  if (ret < 0) {
    return search_in_name_node(item->left, root, itemName);
  } 

  else if (ret > 0) {
    return search_in_name_node(item->right, root, itemName);
  }

  else {
    return item;
  }

}

//insert node into to create trees
item_node *insert ( item_node *parent, item_node *new_node) 
{
  int ret = strcmp(parent->name, new_node->name);

  if (ret > 0)
  {

    if (parent->left != NULL)
    {
      return insert(parent->left, new_node);
    }

    else 
    {
      set_left_child_item(parent, new_node);
      return new_node;
    }
   
  }

  else {

    if(parent->right != NULL)
    {
      return insert(parent->right, new_node);
    }

    else 
    {
      set_right_child_item(parent, new_node);
      return new_node;
    }

  }
}

//sort the tree name array in lexographical 
void selection_sort (tree_name_node *root[], int ArrayLength) 
{
  int i, j;
  int minIndex;
  tree_name_node *temp; 
 
  for (i = 0; i < ArrayLength; i++) 
  {
    minIndex = i;
    if(root[i] == NULL)
      continue;
    for (j = i; j < ArrayLength; j++) 
    {
      if(root[j] == NULL)
        continue;
      if ((strcmp(root[j]->treeName, root[minIndex]->treeName) < 0))
      {
        minIndex = j;
      }
    }

      if(minIndex != i)
      {
        temp = root[i];
        root[i] = root[minIndex];
        root[minIndex]= temp;
      }
  }

}

// This function is printing its nodes in preorder. 
void print_tree_Preorder (FILE *ofp, tree_name_node *root)
{

 if (root == NULL)
 {
   return;
 }
  fprintf(ofp, "%s ", root->treeName);
//recursive on the left
  if (root->left) 
  {
    print_tree_Preorder(ofp, root->left);
  } 
//recursive on the right
  if (root->right) 
  {
    print_tree_Preorder(ofp, root->right);
  } 
}

//transverse the tree in  order of the lexographical
void transverse_in_order (FILE *ofp, item_node *item) {
  if (item != NULL) {
    transverse_in_order(ofp, item->left);
    fprintf(ofp, "%s ", item->name);
    transverse_in_order(ofp, item->right);
  }
}

//print the "bottom half" subtree function
void print_subtrees(FILE *ofp, tree_name_node *root)
{
    fprintf(ofp, "\n===%s===\n", root->treeName);
    transverse_in_order(ofp, root->theTree);

    fprintf(ofp, "\n===%s===\n", root->left->treeName);
    transverse_in_order(ofp, root->left->theTree);
    
    fprintf(ofp, "\n===%s===\n", root->right->treeName);
    transverse_in_order(ofp, root->right->theTree);

    fprintf(ofp, "\n===%s===\n", root->right->left->treeName);
    transverse_in_order(ofp, root->right->left->theTree);
}
//find the root that has the same tree name and then do the call the delete to delete that node
void find_and_delete_tree(FILE *ofp, char *command, char *treeName, tree_name_node *root) {
  int ret;

  if(root == NULL)
  {
    fprintf(ofp, "%s does not exist\n", treeName);
    return;
  }
  else if (search_for_name_node(root, treeName) != NULL)
  {
    fprintf(ofp, "%s is deleted\n", root->treeName);

    delete_tree(search_for_name_node(root, treeName));
  }
  else if (search_for_name_node(root->left, treeName) != NULL)
  {
    fprintf(ofp, "%s is deleted\n", root->left->treeName);
    
    delete_tree(search_for_name_node(root->left, treeName));
  }

  else if (search_for_name_node(root->right, treeName) != NULL)
  {
    fprintf(ofp, "%s is deleted\n", root->right->treeName);
    
    delete_tree(search_for_name_node(root->right, treeName));
  }

  else if (search_for_name_node(root->right->left, treeName) != NULL)
  {
    fprintf(ofp, "%s is deleted\n", root->right->left->treeName);
    
    delete_tree(search_for_name_node(root->right->left, treeName));
  }
}

//Call the height_balance function and print out the information
void find_height (FILE *ofp, char *command, char *treeName, tree_name_node *root) 
{
  int ret;
  int ret2;
  int difference;
  
  if (root == NULL)
  {
    fprintf(ofp, "%s does not exist\n", treeName);
    return;
  }
  
  else if ((ret2 = strcmp(treeName, root->treeName)==0))
  {
    int left_height = height_balance(root->theTree->left);

    int right_height = height_balance(root->theTree->right);

    difference = abs(right_height - left_height);

    if (difference > 1) {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", root->treeName, left_height, right_height, difference);
    }
    else {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", root->treeName, left_height, right_height, difference);
    }
  
  }

  else if ((ret2 = strcmp(treeName, root->left->treeName)==0))
  {
    int left_height = height_balance(root->left->theTree->left);

    int right_height = height_balance(root->left->theTree->right);

    difference = abs(right_height - left_height);

    if (difference > 1) 
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", root->left->treeName, left_height, right_height, difference);
    }

    else 
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", root->left->treeName, left_height, right_height, difference);
    }

  }

 else if ((ret2 = strcmp(treeName, root->right->treeName)==0))
  {
    int left_height = height_balance(root->right->theTree->left);

    int right_height = height_balance(root->right->theTree->right);

    difference = abs(right_height - left_height);

    if (difference > 1) 
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", root->right->treeName, left_height, right_height, difference);
    }

    else
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", root->right->treeName, left_height, right_height, difference);
    }
  }

  else if ((ret2 = strcmp(treeName, root->right->left->treeName)==0))
  {
   int left_height = height_balance(root->right->left->theTree->left);

   int right_height = height_balance(root->right->left->theTree->right);

   difference = abs(right_height - left_height);

    if (difference > 1) 
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", root->right->left->treeName, left_height, right_height, difference);
    }
    else 
    {
      fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", root->right->left->treeName, left_height, right_height, difference);
    }
  }

}
//shell to call the count function 
void sum_of_subtrees_shell (FILE *ofp, char *command, char *treeName, tree_name_node *root) {
  int ret;
  int ret2;
  int difference;
  
  if (root == NULL)
  {
    fprintf(ofp, "%s does not exist\n", treeName);
    return;
  }
  
  else if ((ret2 = strcmp(treeName, root->treeName)==0))
  {
    fprintf(ofp, "%s count %d\n", root->treeName, count(root->theTree));
  }

  else if ((ret2 = strcmp(treeName, root->left->treeName)==0))
  {
    fprintf(ofp, "%s count %d\n", root->left->treeName, count(root->left->theTree));
  }

 else if ((ret2 = strcmp(treeName, root->right->treeName)==0))
  {
   fprintf(ofp, "%s count %d\n", root->right->treeName, count(root->right->theTree));
  }

  else if ((ret2 = strcmp(treeName, root->right->left->treeName)==0))
  {
   fprintf(ofp, "%s count %d\n", root->right->left->treeName, count(root->right->left->theTree));
  }
}

//Shell to call the delete_item_in_tree, search_in_name_node, and item_before function
void Processing_commands (FILE *ofp, char *command, char *treeName, tree_name_node *root, char *itemName) {

  int ret;
  int ret2;
  if ((ret = strcmp("delete", command) == 0)) {
   if ((ret2 = strcmp (treeName, root->treeName)) == 0) {
          if (search_in_name_node(root->theTree, root, itemName) != NULL) 
          {
            delete_item_in_tree(root, search_in_name_node(root->theTree, root, itemName), itemName);
            fprintf(ofp, "%s is deleted in the %s\n", itemName, root->treeName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->treeName);
          }
      }

      else if ((ret2 = strcmp (treeName, root->left->treeName)) == 0) 
      {
        if (search_in_name_node(root->left->theTree, root->left, itemName) != NULL) 
          {
            delete_item_in_tree(root->left,search_in_name_node(root->left->theTree, root->left, itemName), itemName);
            fprintf(ofp, "%s is deleted in the %s\n", itemName, root->left->treeName);

          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->left->treeName);
          }
      }
      else if (((ret2 = strcmp (treeName, root->right->treeName)) == 0)) 
      {
        if (search_in_name_node(root->right->theTree, root->right, itemName) != NULL) 
          {
            fprintf(ofp, "%s is deleted in the %s\n", itemName, root->right->treeName);
            delete_item_in_tree(root->right, search_in_name_node(root->right->theTree, root->right, itemName), itemName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->right->treeName);
          }
      }
      else if (((ret2 = strcmp (treeName, root->right->left->treeName)) == 0)) 
      {
        if (search_in_name_node(root->right->left->theTree, root->right->left, itemName) != NULL) 
          {
            fprintf(ofp, "%s is deleted in the %s\n", itemName, root->right->left->treeName);
            delete_item_in_tree(root->right->left, search_in_name_node(root->right->left->theTree, root->right->left, itemName), itemName);
          }
          else
          {
            fprintf(ofp, "%s not found %s\n", itemName, root->right->left->treeName);
          }
      }
      else {
        fprintf(ofp, "%s does not exist\n", treeName);
      }
    }

  else if ((ret = strcmp("search", command)) == 0) {
      if ((ret2 = strcmp (treeName, root->treeName)) == 0) {
          if (search_in_name_node(root->theTree, root, itemName) != NULL) 
          {
            fprintf(ofp, "%d %s is found in the %s\n", search_in_name_node(root->theTree, root, itemName)->count, search_in_name_node(root->theTree, root, itemName)->name, root->treeName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->treeName);
          }
      }

      else if ((ret2 = strcmp (treeName, root->left->treeName)) == 0) 
      {
       if (search_in_name_node(root->left->theTree, root->left, itemName) != NULL) 
          {
            fprintf(ofp, "%d %s is found in the %s\n", search_in_name_node(root->left->theTree, root->left, itemName)->count, search_in_name_node(root->left->theTree, root->left, itemName)->name, root->left->treeName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->left->treeName);
          } 
      }
      else if (((ret2 = strcmp (treeName, root->right->treeName)) == 0)) 
      {
        if (search_in_name_node(root->right->theTree, root->right, itemName) != NULL) 
          {
            fprintf(ofp, "%d %s is found in the %s\n", search_in_name_node(root->right->theTree, root->right, itemName)->count, search_in_name_node(root->right->theTree, root->right, itemName)->name, root->right->treeName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->right->treeName);
          } 
      }
      else if (((ret2 = strcmp (treeName, root->right->left->treeName)) == 0)) 
      {
        if (search_in_name_node(root->right->left->theTree, root->right->left, itemName) != NULL) 
          {
            fprintf(ofp, "%d %s is found in the %s\n", search_in_name_node(root->right->left->theTree, root->right->left, itemName)->count, search_in_name_node(root->right->left->theTree, root->right->left, itemName)->name, root->right->left->treeName);
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->right->left->treeName);
          } 
      }
      else {
        fprintf(ofp, "%s does not exist\n", treeName);
      }
    }
  else if ((ret = strcmp("item_before", command))==0){
    if((ret2 = strcmp(treeName, root->treeName)==0)) 
      {
          if(search_in_name_node(root->theTree, root, itemName) != NULL)
          {
            fprintf(ofp, "item before %s: %d\n",itemName, item_before(root->theTree, itemName, 0));
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->treeName);
          }
      }
      else if((ret2 = strcmp(treeName, root->left->treeName)==0)) 
      {
          if(search_in_name_node(root->left->theTree, root->left, itemName) != NULL)
          {
            fprintf(ofp, "item before %s: %d\n",itemName, item_before(root->left->theTree, itemName, 0));
          }
          else 
          {
            fprintf(ofp, "%s not found in %s\n", itemName, root->left->treeName);
          }
    }
    else if((ret2 = strcmp(treeName, root->right->treeName)==0))
    {
      if(search_in_name_node(root->right->theTree, root->right, itemName) != NULL)
      {
          fprintf(ofp, "item before %s: %d\n",itemName, item_before(root->right->theTree, itemName, 0));
      }
      else 
      {
        fprintf(ofp, "%s not found in %s\n", itemName, root->right->treeName);
      }
    }
    else if((ret2 = strcmp(treeName, root->right->left->treeName)==0)) 
    {
      if(search_in_name_node(root->right->left->theTree, root->right->left, itemName) != NULL)
      {
          fprintf(ofp, "item before %s: %d\n",itemName, item_before(root->right->left->theTree, itemName, 0));
      }
      else 
      {
        fprintf(ofp, "%s not found in %s\n", itemName, root->right->left->treeName);
      }
    }
   else 
   {
      fprintf(ofp, "%s does not exist\n", treeName);
    }
  }
}

//this function is just read lines and will just passing stuff into other function. It consists of pass into the sorting as well.
void read_lines (FILE *ifp, FILE *ofp) {
  
  int num_trees;
  int num_items;
  int num_commands;
  char treeName[32];
  char itemName[32];
  int count;
  char commands[32];
 
  fscanf(ifp, "%d %d %d", &num_trees, &num_items, &num_commands);

  tree_name_node *tree[num_trees];

  for (int i = 0; i < num_trees; i++)
  {
    fscanf(ifp, "%s", treeName);

    tree[i] = new_tree_node(treeName);
  }

  int length = sizeof(tree) / sizeof(tree[0]);

  for (int i = 0; i < num_items; i++)
  {
    fscanf (ifp, "%s %s %d", treeName, itemName, &count);
   for (int j = 0; j < num_trees; j++) {

      int ret = strcmp(treeName, tree[j]->treeName);

      if (ret == 0)
      {
        if (tree[j]->theTree == NULL) //this will only set the root if it was NULL;
        {
          tree[j]->theTree = new_item_node(itemName, count);
        }
        else {
          insert(tree[j]->theTree, new_item_node(itemName, count));  
        }
      }
    }
  }

  selection_sort(tree, length);

  tree_name_node *root = tree[0];
  root->left = tree[1];
  root->right = tree[2];
  root->right->left = tree[3];

  print_tree_Preorder(ofp, root);
  print_subtrees(ofp, root);

  fprintf(ofp, "\n=====Processing Commands=====\n");
    
    for (int i = 0; i < 7; i++) {
      fscanf(ifp, "%s %s %s", commands, treeName, itemName);
      

      Processing_commands(ofp, commands, treeName, root, itemName);
    }

    for (int i = 0; i < 3; i++) {
      fscanf(ifp, "%s %s", commands, treeName);

      find_height(ofp, commands, treeName, root);
    }

    fscanf(ifp, "%s %s %s", commands, treeName, itemName);
    
    Processing_commands(ofp, commands, treeName, root, itemName);

    for (int i = 0; i < 2; i++) {
      fscanf(ifp, "%s %s", commands, treeName);

      sum_of_subtrees_shell(ofp, commands, treeName, root);
    }

    for (int i = 0; i < 2; i++) {
      fscanf(ifp, "%s %s %s", commands, treeName, itemName);

      Processing_commands(ofp, commands, treeName, root, itemName);
    }

    fscanf(ifp, "%s %s", commands, treeName);

    sum_of_subtrees_shell(ofp, commands, treeName, root);

    for (int i = 0; i < 2; i++) 
    {
      fscanf(ifp, "%s %s %s", commands, treeName, itemName);

      Processing_commands(ofp, commands, treeName, root, itemName);
    }

  fscanf(ifp, "%s %s", commands, treeName);

  find_and_delete_tree(ofp,commands, treeName, root);
}

void open_file (FILE *ifp, FILE *ofp) 
{
  ifp = fopen("cop3502-as4-gerber-input.txt", "r");

  if(ifp == NULL) 
  {
  printf("The File isn't available, please double check");
  }

  ofp = fopen("cop3502-as4-pham-quang-output.txt", "w");

  read_lines(ifp, ofp);
}

int main(void) {
  FILE *ifp;
  FILE *ofp;
  open_file(ifp, ofp);
}