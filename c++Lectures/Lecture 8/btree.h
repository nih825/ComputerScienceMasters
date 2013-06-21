
class btree
{
    public:
        btree();
		btree( const btree& t ) = delete;
		btree& operator=( const btree& t ) = delete;
		btree( btree&& t ) : root(t.root) { 
			t.root = NULL;
		}
		btree& operator=( btree&& t ) {
			node* temp = t.root;
			t.root = this->root;
			this->root = temp;
			return *this;
		}
        ~btree();

        void insert(int key);
        node *search(int key);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);
        
        node *root;
};



/*
void example code()
{
	btree t;
	// populate t
	btree t2;
	t2 = std::move(t);        // explicit rvalue reference creation
	t2 = btree("data.txt");   // implicit rvalue reference creation (imagining that btree has a constructor taking string, to read itself in from a file).
}
*/
