#pragma once
#ifndef _SPEECH_MANAGER_H_
#define _SPEECH_MANAGER_H_

#include "SpeechRule.h"

#include <iostream>

using namespace std;

// �˵�����
typedef enum _MENUTYPE_
{
    MAIN_MENU,      // ���˵�
}MenuType;

class SpeechManager
{
public:
    SpeechManager();
    ~SpeechManager();

    // ��ʾ�˵�
    void showMenu(MenuType menuType);

    // ������������
    void publishRules();
    
    // �鿴����
    void showRules();

    // �˳�ϵͳ
    void exitSystem();

private:
    void showMainMenu();

public:
    SpeechRule          *m_speechRule;          // ��������

private:
    bool                m_isSetRule;            // �Ƿ������ù���
};

#endif // !_SPEECH_MANAGER_H_