/*
 * Copyright (c) 2011-2014 stlf@live.cn.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
import bb.cascades.pickers 1.0
import bb.system 1.0

TabbedPane{
    showTabsOnActionBar: false
    Tab {
        imageSource: "asset:///action_icons/ic_view_list.png"
        title: "Browser"

        NavigationPane {
            id: browser                        
            function listdir()
            {
                var file_items = _app.listDir()
                
                model_data.clear()
                
                model_data.append(file_items)
                
                if(_app.pwd() === "/")
                    to_parent_dir.enabled = false
                else
                    to_parent_dir.enabled = true
                
                cur_dir.text = _app.pwd()
            }
            
            Page
            {
                
                onCreationCompleted: {
                    model_data.clear()
                    login.relogin()
                }
                
                titleBar: TitleBar {
                    id: title_bar
                    title: "Upyun Cloud"
                    acceptAction: ActionItem {
                        id: to_parent_dir
                        imageSource: "asset:///action_icons/ic_to_top.png"
                        onTriggered: {
                            _app.gotoParentDir()
                            browser.listdir()
                        }
                    }
                }
                
                Container {
                    Label {
                        id: cur_dir
                    }
                    
                    ListView {
                        dataModel: ArrayDataModel {
                            id: model_data
                        }
                        
                        function  remove_comfirm(name)
                        {
                            dialog.title = "Comfirm"
                            dialog.body = "Remove " + name + " ?"
                            dialog.exec()
                            
                            if (dialog.result === SystemUiResult.CancelButtonSelection)
                                return false
                            return true
                        }
                        
                        function removeDir(dir_name)
                        {
                            if(remove_comfirm(dir_name)){
                                if(_app.removeDir(dir_name)){
                                    toast.body = "Remove dir: " + dir_name + " succeed!"                                  
                                }
                                else {
                                    toast.body = "Remove dir: " + dir_name + " failed! \n This dir is not empty?" 
                                }
                                toast.show()
                            }
                                
                            browser.listdir()
                        }
                        function removeFile(file_name)
                        {
                            if(remove_comfirm(file_name)){
                                if(_app.removeFile(file_name)){
                                    toast.body = "Remove file: " + file_name + " succeed!"
                                    toast.show()
                                }
                            }
                            browser.listdir()
                        }
                        function listdir()
                        {
                            browser.listdir()
                        }
                        function save(name)
                        {
                            if(_app.downloadFile(name))
                            {
                                toast.body = "Down load file: " + name + " succeed! \nYou can find it in downloads directory."
                                toast.show()
                            }
                        }
                        function  open_extern_link(name)
                        {
                            _app.openExternLink(name)
                        }    
                    
                        
                        accessibility.name: "TODO: Add property content"
                        
                        property bool isloading: false
                        onTriggered: {
                            var chosenItem = dataModel.data(indexPath)
                            if(isloading)
                                return
                            if(chosenItem.size === "")
                            {
                                isloading = true
                                _app.cd(chosenItem.name)
                                
                                browser.listdir()
                                isloading = false

                            }
                        }
                        
                        listItemComponents: [
                            ListItemComponent {
                                StandardListItem {
                                    id: file_list_item
                                    accessibility.description: ""
                                    imageSource: ListItemData.type === "F" ?
                                                     "asset:///images/folder.png":"asset:///images/documents.png"
                                    title: ListItemData.name
                                    status: ListItemData.size
                                    description: ListItemData.date	
                                    accessibility.name: "TODO: Add property content"
                                    
                                    contextActions: [
                                        ActionSet {
                                            title: ListItemData.name
                                            actions: [
                                                ActionItem {
                                                    title: "Save"
                                                    onTriggered: {
                                                        file_list_item.ListItem.view.save(ListItemData.name)
                                                    }
                                                    imageSource: "asset:///action_icons/ic_save_as.png"
                                                },
                                                ActionItem {
                                                    title: "Open extern link"
                                                    onTriggered: {
                                                        file_list_item.ListItem.view.open_extern_link(ListItemData.name)
                                                    }
                                                    imageSource: "asset:///action_icons/ic_browser.png"

                                                },
                                                ActionItem {
                                                    title: "Remove"
                                                    onTriggered: {
                                                        
                                                        if(ListItemData.size === "")
                                                        {
                                                            file_list_item.ListItem.view.removeDir(ListItemData.name)
                                                        }
                                                        else
                                                        {
                                                            file_list_item.ListItem.view.removeFile(ListItemData.name)
                                                        }
                                                        
                                                        file_list_item.ListItem.view.listdir()
                                                    }
                                                    imageSource: "asset:///action_icons/ic_delete.png"
                                                }
                                            ]

                                        }
                                    ]

                                }

                            }
                        ]
                    }

                }
                
                actions: [
                    ActionItem {
                        title: "Upoad file"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            file_picker.open()

                        }
                        imageSource: "asset:///action_icons/ic_add_entry.png"
                    },
                    ActionItem {
                        title: "Add folder"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            add_folder_prompt.exec()

                        }
                        imageSource: "asset:///action_icons/ic_add_folder.png"
                    },
                    ActionItem {
                        title: "Refresh"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            browser.listdir()
                        }
                        imageSource: "asset:///action_icons/ic_reload.png"

                    },
                    ActionItem {
                        title: "Get bucket usage"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            toast.body = "Used: " + Number(login.usage) / 1000.0 + "KB";
                            toast.show()
                        }
                        imageSource: "asset:///action_icons/ic_browse.png"
                    
                    },
                    ActionItem {
                        title: "Login out"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            model_data.clear()
                            login.relogin()
                        }

                    }


                ]

            }
            attachedObjects: [
                ComponentDefinition {
                    id: dir;
                    source: "main.qml"
                },
                SystemToast {
                    id: toast
                },
                SystemDialog {
                    id: dialog
                },
                FilePicker {
                    id: file_picker
                    
                    title: qsTr ("Select the file to upload:")
                    
                    onFileSelected: {
                        var selectf = selectedFiles[0]
                        if(selectf === "")
                            return;
                        if(mode === FilePickerMode.Saver)
                        {
                        }
                        else
                        {
                            if(_app.uploadFile(selectf))
                            {
                                toast.body = "Upload file succeed!"
                                toast.show()
                                
                                browser.listdir()
                            }
                        }
                    }

                },
                SystemPrompt{
                    id: add_folder_prompt
                    
                    onFinished: {
                        var dir_name = inputFieldTextEntry()
                        if (value === SystemUiResult.ConfirmButtonSelection)
                        {
                            if (_app.makeDir(dir_name.trim())) {
                                toast.body = "Make dir succeed!"
                                
                                toast.show()
                                
                                browser.listdir()

                            }
                        }
                    }
                    title: "Make dir"
                    body: "Input remote dir name: "
                },
                Login {
                    id: login
                    onClosed: {
                        browser.listdir()
                        title_bar.title = login.bucket_name;
                        
                    }
                }
            ]
            onPopTransitionEnded: {
                page.destroy();
            }
        }
        
    }
    Tab {
        AboutPage {}
        imageSource: "asset:///action_icons/ic_info.png"
        title: "About"
    }
}
