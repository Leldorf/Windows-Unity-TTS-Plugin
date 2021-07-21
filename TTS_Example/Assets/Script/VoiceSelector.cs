using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class VoiceSelector : MonoBehaviour
{
    [SerializeField]
    TTS tts = null;
    Dropdown selector;
    // Start is called before the first frame update
    void Start()
    {
        selector = GetComponent<Dropdown>();

        if(tts == null)
        {
            tts = GameObject.Find("TTS").GetComponent<TTS>();
        }
        List<string> names = tts.GetVoiceNmaes();

        foreach(string name in names)
        {
            Dropdown.OptionData option = new Dropdown.OptionData();
            option.text = name;
            selector.options.Add(option);
        }
        selector.value = names.Count-1;
        SelectVoice();
    }
    public void SelectVoice()
    {
        Debug.Log(selector.value);
        tts.SetVoice(selector.value);
    }
}
