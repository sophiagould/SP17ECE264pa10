#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	//fill in
	PathNode * bye = p -> head;
	PathNode * temp;
	while(bye != NULL){
		temp = bye;
		bye = bye -> next;
		freeNode(temp);
	}
	free(p);
}

PathNode * buildNode(char * path) {
	//fill in
	PathNode * pano = malloc(sizeof(PathNode));
	pano -> path = malloc(sizeof(char) * strlen(path) + 1);
	pano -> next = NULL;
	strcpy(pano->path,path);
	return pano;
}
	
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.


void freeNode(PathNode * p) {
	//fill in
	free(p -> path);
	free(p);
	return;
}

bool addNode(PathLL * paths, char * path) {
	if(containsNode(paths,path)){
		return false;
	}
	PathNode * tum;
	PathNode * pont;
	pont = buildNode(path);
	tum = paths -> head;
	if(tum == NULL){
		paths -> head = pont;
		return true;
	}
	//add to begining
	if(comp(path, tum->path)){
		pont -> next = paths -> head;
		paths -> head = pont;
		return true;
	}
	//add to middle
	while(tum -> next != NULL){
		if(comp(path, tum -> next -> path)){
			pont -> next = tum -> next;
			tum -> next = pont;
			return true;
		}
		tum = tum -> next;
	}
	//add to end
	tum -> next = pont;
	return true;	
}

bool comp(char * p1, char * p2){
	bool val1;
	bool val2;
	bool val3;
	bool ret;
	val1 = strlen(p1) < strlen(p2);
	val2 = ((strlen(p1) == strlen(p2)) && (numturns(p1) < numturns(p2)));
	val3 = ((strlen(p1) == strlen(p2)) && (numturns(p1) == numturns(p2)) && (strcmp(p1, p2) < 0));
	ret = (val1 || val2 || val3);
	return ret;
}

int numturns(char * path){
	int x = 0;
	int numturn = 0;
	while(path[x+1] != '\0'){
		if(path[x] != path[x+1]){
			numturn++;
		}
		x++;
	}
	return numturn;
}

bool removeNode(PathLL * paths, char * path) {
  //fill in
	bool fact;
	fact = containsNode(paths, path);
	if(fact == false){
		return false;
	}
	PathNode * he = paths -> head;
	while(strcmp(path, he->next->path) != 0){
		he = he ->next;
	}
	PathNode * test;
	test = he -> next;
	he->next = he->next->next;
	freeNode(test);
	return true;
}

bool containsNode(PathLL * paths, char * path) {
	PathNode * heads = paths -> head;
	while(heads != NULL){
		if(strcmp(path, heads -> path) ==0){
			return true;
		}
		heads = heads -> next;
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
