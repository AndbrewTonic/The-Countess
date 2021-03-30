#include <string>
#include <iostream>
#define FIRST_CHAR 'A'
#define ALPHABET_SIZE 26
using namespace std;

struct Node {
	Node* children[ALPHABET_SIZE];
	bool end;

	Node() {
		for(int i = 0; i < ALPHABET_SIZE; i++)
			children[i] = NULL;
		end = false;
	}

	bool isEmpty() {
		for(int i = 0; i < ALPHABET_SIZE; i++)
			if(children[i] != NULL) return false;
		return true;
	}
};

bool search(const Node&, string, int = 0);
void insert(Node&, string, int = 0);
Node* remove(Node&, string, int = 0);
void autocomplete(const Node&, string = "");

int main() {
	string keys[] = { "THE", "A", "THERE",
                      "ANSWER", "ANY", "BY",
                      "BYE", "THEIR", "HERO", "HEROPLANE" };
	int n = *(&keys+1)-keys;
	Node root;
	for(int i = 0; i < n; i++)
		insert(root, keys[i]);
	autocomplete(root);
	cout << "\n";
	autocomplete(*root.children[0], "A");
	cout << "\n";
	search(root, "THE") ? cout << "Yes\n" : cout << "No\n";
	search(root, "THESE") ? cout << "Yes\n" : cout << "No\n";
	remove(root, "HEROPLANE");
	autocomplete(root);
	cout << "\n";
	search(root, "HERO") ? cout << "Yes\n" : cout << "No\n";
	return 0;
}

bool search(const Node& node, string key, int depth) {
	if(depth == key.length()) return node.end;
	int index = key[depth]-FIRST_CHAR;
	if(node.children[index] == NULL) return false;
	return search(*node.children[index], key, depth+1);
}

void insert(Node& node, string key, int depth) {
	if(depth == key.length()) {
		node.end = true;
		return;
	}
	int index = key[depth]-FIRST_CHAR;
	if(node.children[index] == NULL)
		node.children[index] = new Node;
	return insert(*node.children[index], key, depth+1);
}

Node* remove(Node& node, string key, int depth) {
	if(depth == key.length())
		node.end = false;
	else {
		int index = key[depth]-FIRST_CHAR;
		if(node.children[index] == NULL) return &node;
		node.children[index] = remove(*node.children[index], key, depth+1);
	}
	if(node.isEmpty() && !node.end) {
		delete &node;
		return NULL;
	}
	return &node;
}

void autocomplete(const Node& node, string word) {
	if(node.end) cout << word << " ";
	for(int i = 0; i < ALPHABET_SIZE; i++)
		if(node.children[i] != NULL)
			autocomplete(*node.children[i], word+char(FIRST_CHAR+i));
	return;
}
