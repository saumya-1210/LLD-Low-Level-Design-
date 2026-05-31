#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;


//abstraction for document elements
class doc_element{
    public:
    virtual string render()=0;
};

//implementation for image element

class text_element : public doc_element{
    private: 
    string text;

    public:
    text_element(string text){
        this->text=text;
    }
    string render() override{
        return text;
    }
};

class image_element : public doc_element{
    private:
    string imagePath;

    public:

    image_element(string imagePath){
        this->imagePath= imagePath;
    }

    string render() override{
        return "[Image: "+imagePath+"]";
    }
};

class enter : public doc_element{
    public:
    string render() override{
        return "\n";
    }
};

//document class for holding every element
class document{
    private:
    vector<doc_element*>elements;

    public:
    void addElement(doc_element* elem){
        elements.push_back(elem);
    }
    string render(){
        string result;
        for(auto i : elements){
            result+=i->render();
        }
        return result;
    }
};

//file storage implementation

class persistence {
    public:

    virtual void save(string data) = 0;
};

class file_storage : public persistence{
    public:

    void save(string data) override{
        ofstream outFile("doc.txt");
        if(outFile){
            outFile<<data;
            outFile.close();
            cout<<"data has been written to doc.txt"<<endl;
        }
        else{
            cout<<"Error, file is not opening";
        }
    }
};


//Document editor- manages client interactions
class documentEditor{
    private:
    document* doc;
    persistence* store;
    string renderedDoc;

    public:

    documentEditor(document* doc, persistence* store){
        this->doc=doc;
        this->store=store;
    }   

    void addText(string text){
        doc->addElement(new text_element(text));
    }
    void addImage(string path){
        doc->addElement(new image_element(path));
    }
    void addEnter(){
        doc->addElement(new enter());
    }
    string renderDoc(){
        if(renderedDoc.empty()){
            renderedDoc=doc->render();
        }
        return renderedDoc;
    }

    void saveDoc(){
        store->save(renderDoc());
    }
};

int main(){
    document* doc= new document();
    persistence* store=new file_storage();

    documentEditor* editor=new documentEditor(doc, store);
    editor->addText("hello world");
    editor->addEnter();
    editor->addText("example of a simple document editor");

    cout<<editor->renderDoc()<<endl;
    editor->saveDoc();
    return 0;

}