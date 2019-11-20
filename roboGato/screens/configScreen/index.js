import * as React from 'react';
import {
    Alert,
    StyleSheet,
    Text,
    TouchableHighlight,
    View,
    Picker,
} from 'react-native';

import { MaterialCommunityIcons as Icon } from "react-native-vector-icons";


export default class Config extends React.Component {
    static navigationOptions = ({ navigation }) => ({
        header: null
    });

    constructor(props) {
        super(props);
        this.state = {
            playerOneIcon:"",
            playerTwoIcon:"",
            playAgainstPC: false,
        };
    }
    
    _onConfirmPress = () => {
        if(this.state.playerOneIcon == this.state.playerTwoIcon) {
            Alert.alert("Both players cant use the same icon!");
            return
        }
        else {
            this.props.navigation.navigate("GameScreen",{playerOneIcon:this.state.playerOneIcon, playerTwoIcon:this.state.playerTwoIcon});
        }
    }

    render() {
        return (
            <View style={styles.homeBackground}>
                <View style={styles.banner}>
                    <Text style={styles.bannerText}>Select the icon for each player:</Text>
                </View>
                <View>
                    <Text style={styles.Text}>Player One</Text>
                    <Picker selectedValue = {this.state.playerOneIcon}
                            onValueChange={playerOneIcon => this.setState({playerOneIcon})}
                            style={styles.picker}
                            mode = "dropdown">
                            <Picker.Item label="Select an Icon" value="alpha-l"/>
                            <Picker.Item label="L icon" value="alpha-l"/>
                            <Picker.Item label="Dot icon" value="checkbox-blank-circle"/>
                            <Picker.Item label ="Triangle icon" value ="triangle"/>
                    </Picker>
                    <Text style={styles.Text}>Player Two</Text>
                    <Picker selectedValue={this.state.playerTwoIcon}
                            onValueChange={playerTwoIcon => this.setState({ playerTwoIcon })}
                            style={styles.picker}
                            mode="dropdown">
                        <Picker.Item label="Select an Icon" value="alpha-l"/>
                        <Picker.Item label="Dot icon" value="checkbox-blank-circle" />
                        <Picker.Item label="Triangle icon" value="triangle" />
                        <Picker.Item label="L icon" value="alpha-l" />
                    </Picker>
                    
        <TouchableHighlight style={styles.confirmButton} onPress={() => this._onConfirmPress()}>
            <Text style={styles.buttonText}>Confirm</Text>
        </TouchableHighlight>
                </View>
            </View>
        );
    }
}

const styles = StyleSheet.create({
    homeBackground: {
        alignItems: 'center',
        backgroundColor: '#ffffff',
        height: '100%',
        width: '100%'
    },
    banner: {
        backgroundColor: '#161D25',
        paddingVertical: 10,
        height: 80,
        width: '100%',
    },
    picker: {
        width:460,
        marginTop:50,
        marginLeft:150,
    },
    bannerText: {
        color: '#cfedfc',
        fontFamily: 'Roboto',
        fontSize: 20,
        paddingTop: 15,
        textAlign: 'center',
    },
    Text: {
        color: 'black',
        fontFamily: 'Roboto',
        fontSize: 20,
        paddingTop: 15,
        textAlign: 'center',
    },
    confirmButton: {
        alignSelf: 'stretch',
        backgroundColor: 'black',
        marginVertical: 250,
        paddingHorizontal: 130,
        paddingTop: 8,
        paddingVertical: 15,
    },
    buttonText: {
        color: 'white',
        fontFamily: 'Roboto',
        fontSize: 18,
        textAlign: 'center',
    },    

});