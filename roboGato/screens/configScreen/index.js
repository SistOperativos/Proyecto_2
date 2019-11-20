import * as React from 'react';
import {
    FlatList,
    Image,
    StyleSheet,
    Text,
    TouchableHighlight,
    View,
} from 'react-native';

import { CheckBox } from 'react-native-elements';
import { MaterialCommunityIcons as Icon } from "react-native-vector-icons";

class ListItem extends React.PureComponent {

    render() {
        const { item } = this.props
        return (
            <TouchableHighlight underlayColor='#ddddde'
                onPress={item.onPress(item.index)} style={styles.gridItem}>
                <View style={styles.gridItem}>
                    <Text>{item.player}</Text>
                    <Icon name={item.icon} />
                </View>
            </TouchableHighlight>
        )
    }
}

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
            subMenuItems: [
                {
                    
                    icon: "circle-outline",
                    onPress: this._onCirclePress
                },
                {
                    
                    icon: "triangle",
                    onPress: this._onTrianglePress
                },
                {
                    
                    icon: "square",
                    onPress: this._onSquarePress
                }
            ]
        };
    }

    _onCirclePress = (index) => {
        if (index == "One"){
        this.setState({playerOneIcon:"circle-outline"});
        }
        else {
            this.setState({playerTwoIcon:"circle-outline"});
        }
    }
    _onSquarePress = (index) => {
        if (index == "One") {
            this.setState({playerOneIcon:"square"});
        }
        else {
            this.setState({playerTwoIcon: "square"});
        }
    }

    _onTrianglePress = (index) => {
        if (index == "One") {
            this.setState({playerOneIcon:"triange"});
        }
        else {
            this.setState({playerTwoIcon:"triangle"});
        }
    }
    _keyExtrator = (item, index) => index.toString()

    _renderListItem = ({ item, index }) => {
        return (
            <ListItem
                item={item}
                index={index}
                onPressItem={this._onPressItem}
                navigation={this.props.navigation}
            />
        )
    }

    render() {
        return (
            <View style={styles.homeBackground}>
                <View style={styles.banner}>
                    <Text style={styles.bannerText}>Select the icon for each player:</Text>
                </View>
                <View>
                    <FlatList
                        data={this.state.subMenuItems}
                        keyExtractor={this._keyExtrator}
                        renderItem={this._renderListItem}
                        numColumns={2}
                    />
                    <CheckBox title="Play against the PC" checked={()=>{this.setState({playAgainstPC:true})}}/>
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
    bannerText: {
        color: '#cfedfc',
        fontFamily: 'Roboto',
        fontSize: 20,
        paddingTop: 15,
        textAlign: 'center',
    },
    grid: {
        flex: 1,
        justifyContent: 'center',
    },
    gridItem: {
        alignItems: 'center',
        borderRadius: 300,
        borderWidth: 2,
        height: 170,
        justifyContent: 'center',
        margin: 5,
        width: 170,
    },
    title: {
        color: '#161D25',
        fontFamily: 'Roboto',
        fontSize: 12,
        fontWeight: 'bold',
        paddingBottom: 15,
        textAlign: 'center',
    },
    thumbnail: {
        alignSelf: 'center',
        borderRadius: 50,
        borderWidth: 1.5,
        height: 90,
        width: 120
    },
});