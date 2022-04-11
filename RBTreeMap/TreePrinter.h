#pragma once
#include <windows.h>

using namespace std;

template <typename TKey, typename TValue>
class TreePrinter
{

    

    struct DrawNode
    {
        DrawNode* previous;
        string printValue;

        DrawNode(DrawNode* previous, string printValue)
        {
            this->previous = previous;
            this->printValue = printValue;
        }
    };
    
    void DrawNodeRecursive(DrawNode* p)
    {
        if (p == nullptr) {
            return;
        }

        DrawNodeRecursive(p->previous);
        cout << p->printValue;
    }

    List< DrawNode*> drawNodes;
public:
    void PrintTree(RBNode<TKey, TValue>* currentNode, DrawNode* previousDrawNode, bool isLeft)
    {
        if (currentNode == nullptr) 
            return;

        string prevValue = "    ";
        DrawNode* drawNode = new DrawNode(previousDrawNode, prevValue);
        drawNodes.Add(drawNode);
        PrintTree(currentNode->GetRight(), drawNode, true);

        if (!previousDrawNode) 
            drawNode->printValue = "——";
        else if (isLeft)
        {
            drawNode->printValue = ".——";  
            prevValue = "   |";
        }
        else 
        {
            drawNode->printValue = "`——";
            previousDrawNode->printValue = prevValue;
        }

        DrawNodeRecursive(drawNode);
        
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        if(currentNode->IsBlack())//black on white
            SetConsoleTextAttribute(out, 0x0 | 0x70);
        else//red on white
            SetConsoleTextAttribute(out, 0x4 | 0x70);

        cout << " " << currentNode->GetKey() << endl;
        SetConsoleTextAttribute(out,0x0 | 0x70);

        if (previousDrawNode) 
            previousDrawNode->printValue = prevValue;
        
        drawNode->printValue = "   |";

        PrintTree(currentNode->GetLeft(), drawNode, false);
    }

    ~TreePrinter()
    {
        for (size_t i = 0; i < drawNodes.GetSize(); i++)
        {
            delete drawNodes[i];
        }
    }
};



