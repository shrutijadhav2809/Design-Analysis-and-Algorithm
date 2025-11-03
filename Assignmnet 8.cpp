// Shruti Jadhav
// 123B1F035
// 06|10|2025


#include <bits/stdc++.h>
using namespace std;
class Node implements Comparable<Node> {
    int level;             
    int pathCost;          
    int reducedCost;       
    int vertex;            
    vector<Integer> path;    
    int[][] reducedMatrix; 
    Node(int n) {
        reducedMatrix = new int[n][n];
        path = new Arrayvector<>();
    }
    @Override
    public int compareTo(Node other) {
        return Integer.compare(this.reducedCost, other.reducedCost);
    }
}
int main(){
    static final int INT_MAX = 9999999;
    static void copyMatrix(int[][] src, int[][] dest) {
        for (int i = 0; i < src.length; i++)
            System.arraycopy(src[i], 0, dest[i], 0, src.length);
    }
    static int reduceMatrix(int[][] matrix, int n) {
        int reductionCost = 0;
        for (int i = 0; i < n; i++) {
            int rowMin = INT_MAX;
            for (int j = 0; j < n; j++)
                if (matrix[i][j] < rowMin)
                    rowMin = matrix[i][j];
            if (rowMin != INT_MAX && rowMin != 0) {
                reductionCost += rowMin;
                for (int j = 0; j < n; j++)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= rowMin;
            }
        }
        for (int j = 0; j < n; j++) {
            int colMin = INT_MAX;
            for (int i = 0; i < n; i++)
                if (matrix[i][j] < colMin)
                    colMin = matrix[i][j];
            if (colMin != INT_MAX && colMin != 0) {
                reductionCost += colMin;
                for (int i = 0; i < n; i++)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= colMin;
            }
        }
        return reductionCost;
    }
    static Node createNode(int[][] parentMatrix, vector<Integer> path, int level, int i, int j, int n) {
        Node node = new Node(n);
        copyMatrix(parentMatrix, node.reducedMatrix);
        for (int k = 0; level != 0 && k < n; k++)
            node.reducedMatrix[i][k] = INT_MAX;
        for (int k = 0; k < n; k++)
            node.reducedMatrix[k][j] = INT_MAX;
        if (level + 1 < n)
            node.reducedMatrix[j][0] = INT_MAX;
        node.path.addAll(path);
        node.path.add(j);
        node.level = level;
        node.vertex = j;
        return node;
    }
    static void solveTSP(int[][] costMatrix, int n) {
        priority_queue<Node> pq = new priority_queue<>();
        vector<Integer> path = new Arrayvector<>();
        path.add(0);
        Node root = new Node(n);
        copyMatrix(costMatrix, root.reducedMatrix);
        root.path = path;
        root.level = 0;
        root.vertex = 0;
        root.pathCost = 0;
        root.reducedCost = reduceMatrix(root.reducedMatrix, n);
        pq.add(root);
        int minCost = INT_MAX;
        vector<Integer> finalPath = new Arrayvector<>();
        while (!pq.isEmpty()) {
            Node min = pq.poll();
            int i = min.vertex;
            if (min.level == n - 1) {
                min.path.add(0);
                int totalCost = min.pathCost + costMatrix[i][0];
                if (totalCost < minCost) {
                    minCost = totalCost;
                    finalPath = new Arrayvector<>(min.path);
                }
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (min.reducedMatrix[i][j] != INT_MAX) {
                    Node child = createNode(min.reducedMatrix, min.path, min.level + 1, i, j, n);
                    child.pathCost = min.pathCost + costMatrix[i][j];
                    child.reducedCost = child.pathCost + reduceMatrix(child.reducedMatrix, n);
                    pq.add(child);
                }
            }
        }
        cout <<("\nOptimal Delivery Route (SwiftShip): " + finalPath);
        cout <<("Minimum Total Delivery Cost: " + minCost);
    }
    int main() {
        cout <<("Enter number of cities: ");
        int n = ({int x; cin >> x; x;});
        int[][] costMatrix = new int[n][n];
        cout <<("Enter cost matrix (use large number for no direct route):");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                costMatrix[i][j] = ({int x; cin >> x; x;});
        solveTSP(costMatrix, n);
    }
}
