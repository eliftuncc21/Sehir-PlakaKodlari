#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// İkili ağaç düğüm yapısı
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// İkili ağacın ekleme işlemi
TreeNode* insert(TreeNode* root, int data) {
    if (root == nullptr) {
        return new TreeNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// İkili ağacın derinliğini hesaplayan yardımcı işlev
int depth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

// İkili ağacın dengeli olup olmadığını kontrol eden yardımcı işlev
bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    if (abs(leftDepth - rightDepth) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return true;
    }

    return false;
}

// İkili ağacı düzgün bir şekilde görüntülemek için yardımcı işlev
void printTree(TreeNode* root, int level = 0) {
    if (root != nullptr) {
        printTree(root->right, level + 1);

        for (int i = 0; i < level; i++) {
            cout << "   ";
        }
        cout << root->data << endl;

        printTree(root->left, level + 1);
    }
}
// İkili ağacı preorder olarak dolaşan yardımcı işlev
void preorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// İkili ağacı inorder olarak dolaşan yardımcı işlev
void inorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// İkili ağacı postorder olarak dolaşan yardımcı işlev
void postorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
    int main() {
        // Dosya okuma işlemi
        ifstream file("sehir_plaka_kodlari.txt");
        if (!file.is_open()) {
            cout << "Dosya acilamadi." << endl;
            return 1;
        }

        // İki boyutlu dizi oluşturma
        int plakaKodlari[81][2];
        int index = 0;

        string line;
        TreeNode* root = nullptr; // İkili ağaç kök düğümü
        while (getline(file, line)) {
            // Şehir ve plaka kodlarını ayrıştırma
            size_t pos = line.find('\t');
            string sehir = line.substr(0, pos);
            string plakaKoduStr = line.substr(pos + 1);
            int plakaKodu = stoi(plakaKoduStr);

            // Plaka kodunu ikili ağaca ekleme
            root = insert(root, plakaKodu);

            // İki boyutlu diziye ekleme
            plakaKodlari[index][0] = plakaKodu;
            index++;
        }

        file.close();

        // İkili ağacın görüntüsünü ekrana basma
        cout << "Ikili Agac:" << endl;
        printTree(root);

        // İkili ağacın derinliğini ve dengeli olup olmadığını kontrol etme
        cout << "Derinlik: " << depth(root) << endl;

        if (isBalanced(root)) {
            cout << "Ikili Agac Dengeli." << endl;
        } else {
            cout << "Ikili Agac Dengesiz." << endl;
        }

        // İki plaka kodunu kullanıcıdan alma
        int plaka1, plaka2;
        cout << "Birinci plaka kodunu girin: ";
        cin >> plaka1;
        cout << "Ikinci plaka kodunu girin: ";
        cin >> plaka2;

        // Plaka kodlarının şehir isimlerini bulma
        string sehir1, sehir2;
        bool found1 = false, found2 = false;

        file.open("sehir_plaka_kodlari.txt");
        while (getline(file, line)) {
            size_t pos = line.find('\t');
            string sehir = line.substr(0, pos);
            string plakaKoduStr = line.substr(pos + 1);
            int plakaKodu = stoi(plakaKoduStr);

            if (plakaKodu == plaka1) {
                sehir1 = sehir;
                found1 = true;
            }

            if (plakaKodu == plaka2) {
                sehir2 = sehir;
                found2 = true;
            }

            if (found1 && found2) {
                break;
            }
        }

        file.close();

        if (found1) {
            cout << "Birinci plaka kodu (" << plaka1 << ") ile ilgili sehir: " << sehir1 << endl;
        } else {
            cout << "Birinci plaka kodu (" << plaka1 << ") bulunamadi." << endl;
        }
        if (found2) {
                cout << "Ikinci plaka kodu (" << plaka2 << ") ile ilgili sehir: " << sehir2 << endl;
            } else {
                cout << "Ikinci plaka kodu (" << plaka2 << ") bulunamadi." << endl;
            }

            // İki plaka kodunun düzey farkını hesaplama
            TreeNode* node1 = root;
            TreeNode* node2 = root;
            int levelDiff = 0;

            while (node1 != nullptr && node1->data != plaka1) {
                if (plaka1 < node1->data) {
                    node1 = node1->left;
                } else {
                    node1 = node1->right;
                }
                levelDiff++;
            }

            while (node2 != nullptr && node2->data != plaka2) {
                if (plaka2 < node2->data) {
                    node2 = node2->left;
                } else {
                    node2 = node2->right;
                }
                levelDiff--;
            }

            cout << "Duzey Farki: " << abs(levelDiff) << endl;

            // İkili ağacı preorder, inorder ve postorder olarak sıralama ve ekrana basma
            cout << "Preorder: ";
            preorder(root);
            cout << endl;

            cout << "Inorder: ";
            inorder(root);
            cout << endl;

            cout << "Postorder: ";
            postorder(root);
            cout << endl;

            return 0;
        }
