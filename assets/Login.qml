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

Sheet {
    id: loginsheet
    property string bucket_name
    property string usage
    function relogin()
    {
        pass.text = ""
        open()
                
    }
    onOpened: {
        var login_infos = _app.query_login()
        if(login_infos.length){
            check_rem.checked = true
            bucket.text = login_infos[0]["bucket"]
            operator.text = login_infos[0]["user"]
            pass.text = login_infos[0]["pass"]
        }
        else {
            check_rem.checked = false
        }
    }
    Page {
        titleBar: TitleBar {
            
            title: "Login upyun bucket"
            acceptAction: ActionItem {
                title: "Login"
                onTriggered: {
                    usage = _app.login(bucket.text.trim(), 
                    	operator.text.trim(),
                    	pass.text.trim());               
                    if(usage !== "")
                    {
                        if(check_rem.checked)
                        	_app.remember_login(bucket.text.trim(), 
                        		operator.text.trim(),pass.text.trim());
                        else 
                        	_app.forget_login();
                        
                    	bucket_name = bucket.text
                        loginsheet.close()
                    }
                }

            }
            visibility: ChromeVisibility.Default

        }
        Container {
            //background: Color.create("#5aaee2")            
            leftPadding: 68
            rightPadding: 68
            
            horizontalAlignment: HorizontalAlignment.Center

            layout:DockLayout {

            }
            ImageView {               
                horizontalAlignment: HorizontalAlignment.Center
                imageSource: "asset:///images/upyunapp_logo.png"
                loadEffect: ImageViewLoadEffect.FadeZoom
                scalingMethod: ScalingMethod.AspectFit
            }
            
            Container { 
                               
                verticalAlignment: VerticalAlignment.Center

                Label {
                	text: "   "
                	minHeight: 78
                }
                Label {
                    text: "Bucket:"
                }
                TextField {
                    id: bucket
                    text: ""
                }
                
                Label {
                    text: "Operator:"
                }
                TextField {
                    id: operator
                    text: ""
                }
                
                Label {
                    text: "Password:"
                }
                TextField {
                    id: pass
                    inputMode: TextFieldInputMode.Password
                
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    layout: DockLayout {
                    }
                    topMargin: 10.0
                    Label {
                        text: "Rememer login info:"
                    }
                    ToggleButton {
                        id: check_rem
                        horizontalAlignment: HorizontalAlignment.Right

                    }                    
                }

            }

        }
    }
}