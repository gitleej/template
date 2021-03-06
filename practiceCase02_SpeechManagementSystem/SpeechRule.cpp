#include "SpeechRule.h"

SpeechRule::SpeechRule()
{
}

SpeechRule::~SpeechRule()
{
}

void SpeechRule::setRule()
{
    Rule::RuleErrorType ret = Rule::RULE_OK;
    do
    {
        cout << "\n------------- 比赛规则设置 -------------\n"
            << "原则：\n"
            << "1. (海选总人数 / 海选分组数) - 海选每组晋级人数 > 1\n"
            << "2. (海选每组晋级人数 * 海选分组数) % 复赛分组数 = 0\n"
            << "3. 复赛分组数 * 复赛每组晋级人数 > 3" << endl;
        cout << ">>请输入海选总人数：";
        cin >> this->m_auditionNum;
        cout << ">>请输入海选分组数：";
        cin >> this->m_auditionGrpNum;
        cout << ">>请输入海选每组晋级人数：";
        cin >> this->m_auditionNextNum;
        ret = checkRule(0);
        while (ret == Rule::RULE_SF_CANT_AVG || ret == Rule::RULE_TOTAL_LESS || ret == Rule::RULE_ZERO_NUMBER) {
            cout << ">>请输入海选总人数：";
            cin >> this->m_auditionNum;
            cout << ">>请输入海选分组数：";
            cin >> this->m_auditionGrpNum;
            cout << ">>请输入海选每组晋级人数：";
            cin >> this->m_auditionNextNum;
            ret = checkRule(0);
        }
        this->m_semi_finalsNum = this->m_auditionGrpNum * this->m_auditionNextNum;
        cout << ">>请输入复赛分组数：";
        cin >> this->m_sfGrpNum;
        cout << ">>请输入复赛每组晋级人数：";
        cin >> this->m_sfNextNum;
        this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
        ret = checkRule(1);
        while (ret == Rule::RULE_SF_CANT_AVG || ret == Rule::RULE_SF_LESS_FINAL)
        {
            cout << ">>请输入复赛分组数：";
            cin >> this->m_sfGrpNum;
            cout << ">>请输入复赛每组晋级人数：";
            cin >> this->m_sfNextNum;
            this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
            ret = checkRule(1);
        }
    } while (Rule::RULE_OK != ret);
    showRules();

    system("pause");
}

void SpeechRule::showRules()
{
    cout << "\n------------- 比赛规则 -------------\n"
        << "|=海选=                            |\n"
        << "|  参赛总人数: \t\t" << this->m_auditionNum << "\t 人|\n"
        << "|  分组数量数: \t\t" << this->m_auditionGrpNum << "\t 组|\n"
        << "|  每组晋级人数: \t" << this->m_auditionNextNum << "\t 人|\n"
        << "|=复赛=                            |\n"
        << "|  参赛总人数: \t\t" << this->m_semi_finalsNum << "\t 人|\n"
        << "|  分组数量数: \t\t" << this->m_sfGrpNum << "\t 组|\n"
        << "|  每组晋级人数: \t" << this->m_sfNextNum << "\t 人|\n"
        << "|=决赛=                            |\n"
        << "|  参赛总人数: \t\t" << this->m_finalsNum << "\t 人|\n"
        << "|  冠军、亚军、季军各\t1\t 人|\n"
        << "------------------------------------" << endl;
}

void SpeechRule::saveRule(string filename)
{
    string filepath = "./data/rules/" + filename + ".csv";

    ofstream ofs;
    ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    ofs << this->m_auditionNum << "," << this->m_auditionGrpNum << ","
        << this->m_auditionNextNum << endl;
    ofs << this->m_semi_finalsNum << "," << this->m_sfGrpNum << ","
        << this->m_sfNextNum << endl;
    ofs << this->m_finalsNum << endl;

    ofs.close();
}

void SpeechRule::loadRule(string filename) {
    string filepath = "./data/rules/" + filename + ".csv";

    ifstream ifs;
    ifs.open(filepath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        cout << "【错误】：文件不存在。" << filepath << endl;
        return;
    }

    string line;
    vector<string> tempStrSplitResult;
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_auditionNum = stoi(tempStrSplitResult[0]);
    this->m_auditionGrpNum = stoi(tempStrSplitResult[1]);
    this->m_auditionNextNum = stoi(tempStrSplitResult[2]);
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_semi_finalsNum = stoi(tempStrSplitResult[0]);
    this->m_sfGrpNum = stoi(tempStrSplitResult[1]);
    this->m_sfNextNum = stoi(tempStrSplitResult[2]);
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_finalsNum = stoi(tempStrSplitResult[0]);

    ifs.close();
}

Rule::RuleErrorType SpeechRule::checkRule(int level)
{
    if (this->m_auditionGrpNum <= 0 ||
        this->m_auditionNextNum <= 0 ||
        this->m_auditionNum <= 0)
    {
        cout << "错误！请检查规则参数！\n"
            << "海选总人数、海选分组数或海选每组晋级人数小于等于0。" << endl;
        return Rule::RULE_ZERO_NUMBER;
    } 
    else if (this->m_auditionNum % this->m_auditionGrpNum != 0) {
        cout << "错误！请检查规则参数！\n"
             << "海选分组无法均分，请重试！" << endl;
        return Rule::RULE_SF_CANT_AVG;
    }
    else if (this->m_auditionNum <= ((this->m_auditionNextNum + 1) * this->m_auditionGrpNum))
    {
        cout << "错误！请检查规则参数！\n"
            << "海选总人数过少，不满足分组和晋级原则，(总人数 / 分组数) - 每组晋级人数 > 1。" << endl;
        return Rule::RULE_TOTAL_LESS;
    }
    else if(level == 1)
    {
        // 海选符合规则，进行复赛规则检查
        map<int, int> commonDivisor;
        if (this->m_sfGrpNum <=0 ||
            this->m_sfNextNum <=0)
        {
            cout << "错误！请检查规则参数！\n"
                << "复赛分组数或复赛每组晋级人数小于等于0。" << endl;
            return Rule::RULE_ZERO_NUMBER;
        }
        else if(((this->m_auditionNextNum * this->m_auditionGrpNum) % this->m_sfGrpNum) != 0)
        {
            this->getCommonDivisor(this->m_semi_finalsNum, commonDivisor);
            cout << "错误！复赛分组无法均匀分组！\n"
                << "推荐分组数为：\n组数：\t每组人数\n";
            for (auto it = commonDivisor.begin(); it != commonDivisor.end(); it++)
            {
                cout << it->first << "\t" << it->second << endl;
            }
            return Rule::RULE_SF_CANT_AVG;
        }
        else if ((this->m_sfGrpNum * this->m_sfNextNum) <= 3)
        {
            this->getCommonDivisor(this->m_semi_finalsNum, commonDivisor);
            cout << "错误！复赛晋级人数小于等于3人！请重新设置复赛分组方案。\n"
                 << "推荐分组数为：\n组数：\t每组人数\n";
            for (auto it = commonDivisor.begin(); it != commonDivisor.end(); it++)
            {
                cout << it->first << "\t" << it->second << endl;
            }
            return Rule::RULE_SF_LESS_FINAL;
        }
        return Rule::RULE_OK;
    }
    return Rule::RULE_OK;
}

void SpeechRule::getCommonDivisor(const int &src, map<int, int>& dst)
{
    dst.clear();
    for (int i = 1; i * i <= src; i++)
    {
        if (src % i == 0)
        {
            int value = src / i;
            dst.insert(pair<int, int>(i, value));
            if (i *i != src)
            {
                value = i;
                dst.insert(pair<int, int>(src / i, value));
            }
        }
    }
}
