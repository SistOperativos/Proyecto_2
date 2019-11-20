import React from "react"
import BgAudio from 'react-native-background-audio'
import {
    Alert,
    BackHandler,
    StyleSheet,
    Text,
    View,
} from 'react-native';

import { TouchableOpacity } from "react-native-gesture-handler";
import {MaterialCommunityIcons as Icon} from "react-native-vector-icons";
const audio_options = {
    source: { local: require('../../assets/Platformer2.mp3') }
}

export default class Game extends React.Component {
    static navigationOptions = ({ navigation }) => ({
        header: true
    });

    constructor(props) {
        super(props);
        this.state = {
            gameState: [[0,0,0],
                        [0,0,0],
                        [0,0,0]],
            currentPlayer: "Uno",
            playerOneIcon: "",
            playerTwoIcon:"",
        };
    }
    componentDidMount(){
        this.backhandler = BackHandler.addEventListener("hardwareBackPress", ()=>{
            this.props.navigation.navigate('Home');
        });
        const { navigation } = this.props
        this.setState({playerOneIcon: navigation.state.params.playerOneIcon, playerTwoIcon: navigation.state.params.playerTwoIcon})
        
        this.initializeGame();
    }
    componentWillUnmount(){
        this.backhandler.remove();
        const { navigation } = this.props
        this.setState({ playerOneIcon: navigation.state.params.playerOneIcon, playerOneIcon: navigation.state.params.playerTwoIcon })
    }

    initializeGame = () => {
        this.setState({gameState:
            [
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0]
            ],
        })
        this.setState({currentPlayer: "Uno"});
    }

    getWinner = () => {
        for (let i=0; i<3; i++){
            if ((this.state.gameState[i][0] == "Uno") && (this.state.gameState[i][0] == this.state.gameState[i][1]) && (this.state.gameState[i][0] == this.state.gameState[i][2])){
                return "Uno";
            }
            else if ((this.state.gameState[i][0] == "Dos") && (this.state.gameState[i][0] == this.state.gameState[i][1]) && (this.state.gameState[i][0] == this.state.gameState[i][2])){
                return "Dos";
            }
        }
        

        for (let i = 0; i < 3; i++) {
            if ((this.state.gameState[0][i] == "Uno") && (this.state.gameState[0][i] == this.state.gameState[1][i]) && (this.state.gameState[0][i] == this.state.gameState[2][i])) {
                return "Uno";
            }
            else if ((this.state.gameState[0][i] == "Dos") && (this.state.gameState[0][i] == this.state.gameState[1][i]) && (this.state.gameState[0][i] == this.state.gameState[2][i])) {
                return "Dos";
            }
        }
        
        if((this.state.gameState[0][0] == this.state.gameState[1][1]) && (this.state.gameState[2][2] == this.state.gameState[0][0])){
            return this.state.gameState[0][0];
        }
        else if((this.state.gameState[2][0] == this.state.gameState[1][1]) && (this.state.gameState[0][2] == this.state.gameState[1][1])) {
            return this.state.gameState[2][0];
        }
        return false;
        
    } 

    onTilePress = (row,col) => {
        let currentPlayer = this.state.currentPlayer;
        let value = this.state.gameState[row][col];
        if (value != 0) {
            return;
        }
        else {
            let arr = this.state.gameState.slice();
            arr[row][col] = currentPlayer;
            this.setState({gameState:arr});
            
            let nextPlayer = (currentPlayer == "Uno") ? "Dos" : "Uno";
            this.setState({currentPlayer:nextPlayer});
            winner = this.getWinner();
            if(winner != false){
                Alert.alert("Congratulations player"+winner+"~!");
                this.initializeGame();
            }
            let num = row.toString()+col.toString();
             pos = " "
             ico = " "
            
            if(num=="00"){
                if(this.state.currentPlayer == "Uno"){
                    pos ="1";
                    if (this.state.playerOneIcon == "alpha-l"){
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle"){
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 1;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
            }
            else if(num == "01") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 2;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 2;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
            }
            else if (num == "02"){
                if (this.state.currentPlayer == "Uno") {
                    pos = 3;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 3;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }

                }

            }
            else if (num=="10") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 4;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 4;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }

                }

            }
            else if (num =="11"){
                if (this.state.currentPlayer == "Uno") {
                    pos = 5;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 5;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }

                }

            }
            else if (num =="12") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 6;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 6;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }

                }

            }
            else if (num=="20") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 7;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 7;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }

                }

            }
            else if(num=="21") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 8;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 8;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }

            }
            else if (num== "22") {
                if (this.state.currentPlayer == "Uno") {
                    pos = 9;
                    if (this.state.playerOneIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerOneIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
                else {
                    pos = 9;
                    if (this.state.playerTwoIcon == "alpha-l") {
                        ico = "a"
                    }
                    else if (this.state.playerTwoIcon == "checkbox-blank-circle") {
                        ico = "b"
                    }
                    else {
                        ico = "c"
                    }
                }
            }
            msg = "value:"+pos+ico;
            //Alert.alert(msg)
        
            let formdata = new FormData();
            formdata.append(value, msg)
            fetch('http://192.168.100.5:9016/api/move', {
                method: 'POST',
                headers : {
                    Accept: '/',
                    'Content-Type': 'multipart/form-data',
                }, body: formdata
            })
        }
    }
    
    renderIcon = (row, col) => {
        let value = this.state.gameState[row][col];
        switch(value)
        {
            case "Uno": return <Icon name = {this.state.playerOneIcon} style={styles.playerOne}/>
            case "Dos": return <Icon name={this.state.playerTwoIcon} style={styles.playerTwo} />
            default: return <View/>
        }
    }
    _onRestartPress = () =>{
        Alert.alert("Remember to change the paper for the new game")
        this.initializeGame();
    }
    
    render() {
        
        return (
            
            <View style={styles.container}>
                <BgAudio options={audio_options}></BgAudio>
                <View style={{paddingBottom:100}}>
                    <Text style={styles.text}>Es el turno del jugador: {this.state.currentPlayer}</Text>
                </View>
                <View style={{flexDirection: "row"}}>
                    <TouchableOpacity onPress={() => this.onTilePress(0,0)} style={[styles.tile, {borderLeftWidth:0, borderTopWidth:0}]}>
                        {this.renderIcon(0,0)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(0, 1)} style={[styles.tile, { borderTopWidth: 0, }]}>
                        {this.renderIcon(0, 1)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(0, 2)} style={[styles.tile, { borderRightWidth: 0, borderTopWidth: 0 }]}>
                        {this.renderIcon(0, 2)}
                    </TouchableOpacity>
                </View>
                <View style={{ flexDirection: "row" }}>
                    <TouchableOpacity onPress={() => this.onTilePress(1, 0)} style={[styles.tile, { borderLeftWidth: 0}]}>
                        {this.renderIcon(1, 0)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(1, 1)} style={[styles.tile, {  }]}>
                        {this.renderIcon(1, 1)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(1, 2)} style={[styles.tile, { borderRightWidth: 0}]}>
                        {this.renderIcon(1, 2)}
                    </TouchableOpacity>
                </View>
                <View style={{ flexDirection: "row"}}>
                    <TouchableOpacity onPress={() => this.onTilePress(2, 0)} style={[styles.tile, { borderBottomWidth: 0, borderLeftWidth:0 }]}>
                        {this.renderIcon(2, 0)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(2, 1)} style={[styles.tile, {borderBottomWidth:0}]}>
                        {this.renderIcon(2, 1)}
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => this.onTilePress(2, 2)} style={[styles.tile, { borderBottomWidth:0,borderRightWidth:0 }]}>
                        {this.renderIcon(2, 2)}
                    </TouchableOpacity>
                </View>
                <TouchableOpacity style={styles.Button} onPress={()=>this._onRestartPress()}>
                    <Text style={styles.buttonText}>Restart the game!</Text>
                </TouchableOpacity>
            </View>

        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex:1,
        backgroundColor: 'white',
        alignItems: 'center',
        justifyContent: 'center',
    },
    text: {
        color: 'black',
        fontFamily: 'Roboto',
        fontSize: 30,
        fontWeight: 'bold',
        textAlign: 'center',
    },
    tile: {
        borderWidth: 10,
        alignItems: "center",
        width: 110,
        height: 110,
    },
    playerOne: {
        color: 'blue',
        fontSize: 60,
        flex:1,
        alignItems:"center",
        justifyContent: 'center',
    },
    playerTwo: {
        color: "green",
        fontSize: 60,
        flex: 1,
        alignItems: "center",
        justifyContent: 'center',
    },
    Button: {
        alignSelf: 'stretch',
        backgroundColor: 'black',
        marginVertical: 60,
        paddingHorizontal: 130,
        paddingTop: 8,
       //paddingVertical: 15,
    },
    buttonText: {
        color: 'white',
        fontFamily: 'Roboto',
        fontSize: 18,
        textAlign: 'center',
    }, 
});