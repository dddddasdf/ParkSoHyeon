using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

[SerializeField]
public struct DialogData
{
    //��ȭ ���� ����ü
    public NPCIndex ID;    //�ش� ��縦 ����ϴ� ������Ʈ�� ID
    public string Script;   //��� ����
    public int ScriptID;    //����� ID
    public int IsEnd;   //��ȭ ������ Ȯ�ο�
}

public class JsonClass
{
    public List<DialogData> DailogList { get; set; }
}

[System.Serializable]
public class DialogReader : MonoBehaviour
{
    //private Dictionary<int, DialogReader> DicDialogLoadText;
    
    //private int ID; //������Ʈ���� ������ �ִ� ID
    //private int Chapter;    //���� é��
    //private string ScriptText;  //��ȭ ����

    private List<DialogData> DialogList = new List<DialogData>();   //json �Ľ� ���� ���� ����Ʈ

    public JObject JObejctTest;
    


    //private  = new List<DialogData>();

    
    public static DialogReader Instance { get; private set; }   //����ü ����� ���� ����

    private void Awake()
    {
        //����ü ����
        if (null == Instance)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);

            InitDialogData();

            return;
        }
        Destroy(gameObject);
        //����ü ���� ����
    }

    


    public void InitDialogData()
    {
        TextAsset TextStack = Resources.Load("Data/Dialog") as TextAsset;
        string Teststr;
        
        if (TextStack == null)
        {
            Debug.Log("Dailog File Load Failed");
            //return;
        }
        else
        {
            Debug.Log("Dailog File Load Success");
        }
        

        //var JsonTmp = JsonConvert.DeserializeObject<List<DialogData>>(TextStack.text);

        DialogList = JsonConvert.DeserializeObject<List<DialogData>>(TextStack.text);   //����Ʈ�� json ���� ������ȭ�Ͽ� ���


        Teststr = File.ReadAllText(Application.dataPath + "/Resources/Data/DialogTest.json");
        //StreamReader TestReader = File.OpenText(Teststr);
        //JsonTextReader reader = new JsonTextReader(TestReader);

        JObejctTest = JObject.Parse(Teststr);
        Debug.Log(JObejctTest["data"].ToString());


        


        //var jlist = JsonConvert.DeserializeObject<List<DialogReader>>(oj.text);

        //foreach(var data in jlist)
        //{
        //    this.DicDialogLoadText.Add(data.ID, data);
        //}
    }

    public string GetFristDialogScript(NPCIndex NPCID, int ScriptID, out int IsEnd, out int ListIndex)
    {
        //��ȭ ���۽� ù��° ��� �������� �Լ�

        DialogData TemporaryStruct = DialogList.Find(x => x.ID == NPCID && x.ScriptID == ScriptID);   //Find�� ���ٽ� ����� �̳� �����

        ListIndex = DialogList.FindIndex(x => x.ID == NPCID && x.ScriptID == ScriptID);
        IsEnd = TemporaryStruct.IsEnd;

        return TemporaryStruct.Script;
    }
    public string GetNextDialogScript(NPCIndex NPCID, out int IsEnd, int ListIndex)
    {
        //��ȭ���� ù��° ������ ��� �������� �Լ�

        DialogData TemporaryStruct = DialogList[ListIndex];

        IsEnd = TemporaryStruct.IsEnd;

        return TemporaryStruct.Script;
    }

    //��ũ��Ʈ�� ���� �̻��� �� ����...
    //�ƴ� �̻��� �� �������� �𸥴�..
    //�ƴ� �̻��� ��..
    //������ ������ ����
}
