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

export default class App extends React.Component {
    static navigationOptions = ({ navigation }) => ({
        header: true
    });

    constructor(props) {
        super(props);
        this.state = {
            gameState: [[1,0,0],
                        [0,0,0],
                        [0,0,0]],
            currentPlayer: "Uno",
            playerOneIcon: "close",
        };
    }
    componentDidMount(){
        this.backhandler = BackHandler.addEventListener("hardwareBackPress", ()=>{
            this.props.navigation.navigate('Home');
        });
        this.initializeGame();
    }
    componentWillUnmount(){
        this.backhandler.remove();
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
            else if ((this.state.gameState[0][i] == "Dos") && (this.state.gameState[0][i] == this.state.gameState[0][i]) && (this.state.gameState[0][i] == this.state.gameState[2][i])) {
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
        }
    }

    renderIcon = (row, col) => {
        let value = this.state.gameState[row][col];
        switch(value)
        {
            case "Uno": return <Icon name = {this.state.playerOneIcon} style={styles.playerOne}/>
            case "Dos": return <Icon name="circle-outline" style={styles.playerTwo} />
            default: return <View/>
        }
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
    }
});