#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "doublelinkedlist.h"

int main() {
    LinkedList* linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    if(linkedlist == NULL) {
        printf("linkedlist 동적 할당 실패\n");
        return 0;
    }
    printf("테스트 시작!! \n\n");
    createList(linkedlist);
    addNode(linkedlist, 100);
    addNode(linkedlist, 200);
    addNode(linkedlist, 300);

    removeNode(linkedlist, 2);

    searchNode(linkedlist, 1);
    searchNode(linkedlist, 2);

    deleteList(linkedlist);
    printf("\n\n테스트 종료!!\n");
    return 0;
}


// head, tail, current 노드를 생성 및 초기화
_Bool createList(LinkedList* linkedlist) {
    linkedlist->head = (struct Data*)malloc(sizeof(Data));
    linkedlist->tail = (struct Data*)malloc(sizeof(Data));
    linkedlist->current = linkedlist->head;
    printf("메모리 할당 성공\n");
    return TRUE;
}


// 동적 할당한 메모리 반환
_Bool deleteList(LinkedList* linkedlist) {
    // 현재 가리키고 있는 노드 위치 초기화
    linkedlist->current = linkedlist->head;
    struct Data* node = (struct Data*)malloc(sizeof(Data));

    // 만약 node가 메모리 할당에 실패하면
    if(node == NULL) {
        printf("node에 메모리 할당 실패\n");
        return FALSE;
    }

    // node에 head가 가리키는 노드를 저장
    node = linkedlist->current;

    printf("연결 노드 반환 중");
    // 현재 노드가 NULL이 아니라면(마지막 노드가 아니라면)
    while(linkedlist->current != NULL) {
        // node에 현재 노드가 가리키는 노드 저장
        node = linkedlist->current->next;

        // 데이터가 저장되어 있는 노드 메모리 반환
        memset(linkedlist->current, 0xFF, sizeof(linkedlist->current));
        free(linkedlist->current);
        linkedlist->current = node;
        printf(".");
    }
    printf("\n");
    linkedlist->current = NULL;
    printf("연결 노드 메모리 반환 완료\n");

    memset(linkedlist, 0xFF, sizeof(LinkedList));
    free(linkedlist);
    linkedlist = NULL;

    printf("linkedlist 동적 메모리 반환 완료\n");

    return TRUE;
}


// 노드 추가
_Bool addNode(LinkedList* linkedlist, int number) {
    // current가 가리키는 노드 위치 초기화
    linkedlist->current = linkedlist->head;

    // 새로 할당할 노드 동적 할당
    struct Data* newNode = (struct Data*)malloc(sizeof(Data));

    // newNode 할당 실패 시
    if(newNode == NULL) {
        printf("새로운 노드 할당 실패\n");
        return FALSE;
    }

    // 입력받은 데이터를 새로운 노드의 데이터에 대입
    newNode->number = number;

    // 만약 head의 next가 가리키는 노드가 없다면
    if(linkedlist->head->next == NULL) {
        // 처음 노드 설정
        linkedlist->head->previous = NULL;      // 이전 노드는 NULL
        linkedlist->head->next = newNode;       // 다음 노드로 새로운 노드

        // newNode의 다음 노드와 이전 노드 설정
        newNode->next = linkedlist->tail;       // 다음 노드는 마지막 노드
        newNode->previous = linkedlist->head;   // 이전 노드는 처음 노드

        // 마지막 노드 설정
        linkedlist->tail->next = NULL;      // 다음 노드로 NULL을 가리킴
        linkedlist->tail->previous = newNode;      // 이전 노드는 새로운 노드
    }
    // 1개 이상의 기존 데이터 노드가 존재한다면
    else {
        // 현재 노드의 next가 tail을 가리키기 전까지 반복
        while(linkedlist->current->next->next != NULL) {
            linkedlist->current = linkedlist->current->next;
        }

        // 새로운 노드 설정
        newNode->next = linkedlist->current->next;
        newNode->previous = linkedlist->current;

        // 마지막 노드 설정
        linkedlist->current->next = newNode;    // 마지막 노드가 newNode를 가리킴
        linkedlist->current = linkedlist->tail;    // 현재 노드는 마지막 노드
        linkedlist->current->previous = newNode;    // 마지막 노드의 이전 노드는 새로운 노드
    }
    printf("데이터 추가 완료\n");
    return TRUE;
}


// 노드 제거
_Bool removeNode(LinkedList* linkedlist, int index) {
    // 만약 index가 처음(head) 노드를 가리킨다면
    if(index == 0) {
        printf("유효한 범위의 노드 index를 입력해주세요\n");
        return FALSE;
    }

    // 삭제할 노드를 저장할 노드 메모리 할당
    struct Data* node = (struct Data*)malloc(sizeof(Data));

    // 메모리 할당을 실패하면
    if(node == NULL) {
        printf("임시 노드 메모리 할당 실패\n");
        return FALSE;
    }

    // 현재 가리키는 노드 위치 초기화
    while(linkedlist->current->previous != NULL) {
        linkedlist->current = linkedlist->current->previous;
    }

    // index만큼 현재 노드에서 다음 노드로 이동
    for(int i = 0; i < index; i++) {

        // 만약 index가 노드의 유효 범위를 넘어선 경우 
        if(linkedlist->current->next == NULL) {
            printf("유효한 범위의 노드 index를 입력해주세요\n");
            return FALSE;
        }

        // 현재 노드는 다음 노드가 되게 하기
        linkedlist->current = linkedlist->current->next;
    }
    // node는 삭제할 노드
    node = linkedlist->current;

    // 삭제할 노드의 이전 노드 설정
    linkedlist->current = node->previous;
    linkedlist->current->next = node->next;

    // 삭제할 노드의 다음 노드 설정
    linkedlist->current = node->next;
    linkedlist->current->previous = node->previous;
    printf("데이터 삭제 완료\n");
    
    // 삭제할 노드 메모리 반환
    memset(node, 0xFF, sizeof(node));
    free(node);
    node = NULL;

    return TRUE;
}


// 노드 탐색
Data* searchNode(LinkedList* linkedlist, int index) {
    // 만약 index가 처음(head) 노드를 가리킨다면
    if(index == 0) {
        printf("유효한 범위의 노드 index를 입력해주세요\n");
        return FALSE;
    }

    // 현재 가리키는 노드 위치 초기화
    while(linkedlist->current->previous != NULL) {
        linkedlist->current = linkedlist->current->previous;
    }

    // index만큼 현재 노드에서 다음 노드로 이동
    for(int i = 0; i < index; i++) {
        // 만약 index가 노드의 유효 범위를 넘어선 경우 
        if(linkedlist->current->next->next == NULL) {
            printf("유효한 범위의 노드 index를 입력해주세요\n");
            return FALSE;
        }
        // 현재 노드는 다음 노드가 되게 하기
        linkedlist->current = linkedlist->current->next;
    }

    // 해당 index 노드 return
    printf("%d번 째 노드의 데이터는 %d 입니다\n", index, linkedlist->current->number);
    return linkedlist->current;
}
