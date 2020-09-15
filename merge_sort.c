#include <stdio.h>
#include "merge_sort.h"

int min(int a, int b){
  if(a<=b)
    return a;
  else
    return b;
}

// merge the four sub-array
// [low, mid1), [mid1, mid2), [mid2, mid3), [mid3, high)
void merge_4_way(int* array, int low, int mid1, int mid2, int mid3, int high) {
    // IMPLEMENT YOUR CODE HERE
    int l1=mid1-low, l2=mid2-mid1, l3=mid3-mid2, l4=high-mid3;
    int a1[l1], a2[l2], a3[l3], a4[l4];
    for(int i=0; i<l1; ++i)
      a1[i]=array[low+i];
    for(int i=0; i<l2; ++i)
      a2[i]=array[mid1+i];
    for(int i=0; i<l3; ++i)
      a3[i]=array[mid2+i];
    for(int i=0; i<l4; ++i)
      a4[i]=array[mid3+i];
    
    int i=0,j=0,k=0,l=0, idx=low;
    while(i<l1 && j<l2 && k<l3 && l<l4){
      int mn=min(a1[i], min(a2[j], min(a3[k], a4[l])));
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else if(mn==a2[j])
        ++j;
      else if(mn==a3[k])
        ++k;
      else
        ++l;
    }

    while(i<l1 && j<l2 && k<l3){
      int mn=min(a1[i], min(a2[j], a3[k]));
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else if(mn==a2[j])
        ++j;
      else
        ++k;
    }
    while(i<l1 && j<l2 && l<l4){
      int mn=min(a1[i], min(a2[j], a4[l]));
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else if(mn==a2[j])
        ++j;
      else
        ++l;
    }
    while(i<l1 && k<l3 && l<l4){
      int mn=min(a1[i], min(a3[k], a4[l]));
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else if(mn==a3[k])
        ++k;
      else
        ++l;
    }
    while(j<l2 && k<l3 && l<l4){
      int mn=min(a2[j], min(a3[k], a4[l]));
      array[idx]=mn;
      ++idx;
      if(mn==a2[j])
        ++j;
      else if(mn==a3[k])
        ++k;
      else
        ++l;
    }

    while(i<l1 && j<l2){
      int mn=min(a1[i], a2[j]);
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else
        ++j;
    }
    while(i<l1 && k<l3){
      int mn=min(a1[i], a3[k]);
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else
        ++k;
    }
    while(i<l1 && l<l4){
      int mn=min(a1[i], a4[l]);
      array[idx]=mn;
      ++idx;
      if(mn==a1[i])
        ++i;
      else
        ++l;
    }
    while(j<l2 && k<l3){
      int mn=min(a2[j], a3[k]);
      array[idx]=mn;
      ++idx;
      if(mn==a2[j])
        ++j;
      else
        ++k;
    }
    while(j<l2 && l<l4){
      int mn=min(a2[j], a4[l]);
      array[idx]=mn;
      ++idx;
      if(mn==a2[j])
        ++j;
      else
        ++l;
    }
    while(k<l3 && l<l4){
      int mn=min(a3[k], a4[l]);
      array[idx]=mn;
      ++idx;
      if(mn==a3[k])
        ++k;
      else
        ++l;
    }

    while(i<l1){
      array[idx]=a1[i];
      ++idx;
      ++i;
    }
    while(j<l2){
      array[idx]=a2[j];
      ++idx;
      ++j;
    }
    while(k<l3){
      array[idx]=a3[k];
      ++idx;
      ++k;
    }
    while(l<l4){
      array[idx]=a4[l];
      ++idx;
      ++l;
    }

}

// divide the array [low, high) into 4 parts (roughly same size).
// For each part, if # of items > 3, recursively call mergesort_4_way_rec;
// Otherwise sort them as you like
// Finally use merge_4_way merge them
void mergesort_4_way_rec(int* array, int low, int high) {
    // IMPLEMENT YOUR CODE HERE

    if(high-low<=1){
      return;
    }else{
      int q2=(low+high)/2, q1=(low+q2)/2, q3=(q2+high)/2;
      mergesort_4_way_rec(array, low, q1);
      mergesort_4_way_rec(array, q1, q2);
      mergesort_4_way_rec(array, q2, q3);
      mergesort_4_way_rec(array, q3, high);

      merge_4_way(array, low, q1, q2, q3, high);
    }
    
}
