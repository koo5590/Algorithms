template <class T>
class IndexedTree{
public:
    vector<T> tree;
    vector<T> nums;
    int numLen;
    int leafSize, depth;

    IndexedTree(vector<T>& inputNums){
        nums = inputNums; numLen = nums.size()-1;

        depth = 0;
        while(pow(2,depth) < numLen)
            depth++;

        leafSize = (int)pow(2,depth);
        tree = vector<T>(2*leafSize);
    }

    T makeTree(int node){
        if(node>=leafSize) {
            if(node-leafSize+1<=numLen)
                return tree[node] = nums[node - leafSize+1];
            else
                return tree[node] = 0;
        }
        return tree[node] = makeTree(node*2) + makeTree(node*2+1);
    }

    T query(int node, int left, int right, int qLeft, int qRight){
        if(qRight<left || right<qLeft){  //관련 없는 경우
            return 0;
        }
        else if(qLeft<=left && right<=qRight)  //쿼리에 전체가 속하는 경우
            return tree[node];
        else{
            int mid = (left+right)/2;  //쿼리가 걸쳐 있는 경우
            return query(node*2, left, mid, qLeft, qRight) +
                query(node*2+1, mid+1, right, qLeft, qRight);
        }
    }

    void update(int node, int left, int right, int index, T diff){
        if(index<left || right<index)
            return;
        else{
            tree[node] += diff;
            if(left != right){
                int mid = (left+right)/2;
                update(node*2, left, mid, index, diff);
                update(node*2+1, mid+1, right, index, diff);
            }
        }
    }


};
