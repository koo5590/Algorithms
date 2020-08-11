
//upper_bound
int upperBound(vector<int>& list, int target){
    int left = 0;
    int right = list.size();

    while(left<right){
        int mid = (left+right)/2;

        if(list[mid]<=target)
            left = mid+1;
        else
            right = mid;
    }

    return left;
}

//lower_bound
int lowerBound(vector<int>& list, int target){
    int left = 0;
    int right = list.size();

    while(left<right){
        int mid = (left+right)/2;

        if(list[mid]>=target){
            right = mid;
        }
        else{
            left = mid+1;
        }
    }

    return left;
}
