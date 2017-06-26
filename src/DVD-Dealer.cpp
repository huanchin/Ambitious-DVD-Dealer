// **************************************************************************
//  File       [DVD_Dealer.cpp]
//  Author     [Chih-Ming Chang]
//  Synopsis   [The implementation of the DVD_Dealer Class]
//  Modify     [2016/03/15 Chih-Ming Chang]
// **************************************************************************

#include "DVD_Dealer.h"

int Greedy(int Number_of_Songs, int Number_of_DVDs, int DVD_Constraint_Time, vector <int> songs){
	
	cout << 1 << endl;
	//TODO implement Greedy algorithm code here

	int T = DVD_Constraint_Time;	
	int n = Number_of_Songs;
	int *sorted_songs = new int[n+1];
	int ans = 0;
	sorted_songs[0] = 0;
	
	for (int i = 1; i < n+1;i++)
	{
	 sorted_songs[i] = songs[i];
	}
	
	for (int j = 2;j < n+1;j++)
    	{
      		int flag = sorted_songs[j];
      		int i = j-1;
      		while ((i >= 1)&&(sorted_songs[i]>flag))
        	{
          		sorted_songs[i+1]=sorted_songs[i];
          		i=i-1;
        	}
      		sorted_songs[i+1]=flag;
   	 }


	int left = 1;
	int right = Number_of_Songs;
	int middle = (left+right)/2;

	while (1){
	cout << left<<endl;
	cout<<right<<endl;
	int cd = 1;
	int time_left = T;
	int song = 0;	

	for (int i=1 ; (i <= Number_of_Songs) ; i++){

	if (songs[i] <= sorted_songs[middle]&&(songs[i]<=T)){

	   if(songs[i] <= time_left){
		time_left = time_left - songs[i];
		song++;
	   }
	   else{
		cd++;

		if (cd > Number_of_DVDs)
		break;

		song++;
		time_left = T - songs[i];
	   }
	}
    	}	



	if (song >= middle){
	    left = middle;
	    right = right;
	}
	else{
	    left = left;
	    right = middle;
	}
	if (middle==(left+right)/2){
	ans = song;
	break;}
	middle = (left + right)/2;
	}
	delete [] sorted_songs;
	return ans;


	
}

int DynamicProgramming(int Number_of_Songs, int Number_of_DVDs, int DVD_Constraint_Time, vector <int> songs){
	
	cout << 2 << endl;
	//TODO implement Dynamic Programming algorithm code here

	int ***F = new int**[Number_of_Songs+1];

	for (int i = 0; i <= Number_of_Songs; i++){
		F[i] = new int *[Number_of_DVDs+1];

		for (int j = 0; j <= Number_of_DVDs; j++){
			F[i][j] = new int [DVD_Constraint_Time+1];

			for (int k = 0; k <= DVD_Constraint_Time; k++){
			F[i][j][k] = 0;
			}
		}

	}


	for (int i = 1; i <= Number_of_Songs; i++){
	   
	    for (int j = 1; j <= Number_of_DVDs; j++){
	    	for(int k = 0; k <= DVD_Constraint_Time; k++){
		
		if (songs[i] <= k){
		   if (F[i-1][j][k] < F[i-1][j][k-songs[i]]+1)
		      F[i][j][k] = F[i-1][j][k-songs[i]]+1;
		   else 
		      F[i][j][k] = F[i-1][j][k];
		}
		else {
		   if (F[i-1][j][k] < F[i][j-1][DVD_Constraint_Time])
		      F[i][j][k] = F[i][j-1][DVD_Constraint_Time];
		   else 
		      F[i][j][k] = F[i-1][j][k];
		}
		}
	     }
		

	}

	int ans = F[Number_of_Songs][Number_of_DVDs][DVD_Constraint_Time];
	
	for (int i = 0; i <= Number_of_Songs; i++){

		for (int j = 0; j <= Number_of_DVDs; j++){
		    delete [] F[i][j];
		}
		delete [] F[i];

	}
	
	delete [] F;

	return ans;	
	
}


