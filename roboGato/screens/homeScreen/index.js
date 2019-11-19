import * as React from 'react';
import {
  FlatList,
  Image,
  StyleSheet,
  Text,
  TouchableHighlight,
  View,
} from 'react-native';

import IconSettings from '../../assets/settings.png';
import GameIcon from '../../assets/gameIcon.png';

class ListItem extends React.PureComponent {
  
  render() {
    const { item } = this.props
    const { navigation } = this.props
    return (
      <TouchableHighlight style={styles.gridItem}
        onPress={() => navigation.navigate(item.tag)}>
        <View style={styles.gridItem} backgroundColor='#7dceff'>
          <View>
            <Text style={styles.title}> {item.title} </Text>
          </View>
          <Image style={styles.thumbnail} source={item.image} />
          <View />
        </View>
      </TouchableHighlight>
    )
  }
}

export default class Home extends React.Component {
  static navigationOptions = ({ navigation }) => ({
    header: null
  });

  constructor(props) {
    super(props);
    this.state = {
      gridItems: [
        {
          image: GameIcon,
          tag: 'GameScreen',
          title: 'GameScreen'
        },
        {
          image: IconSettings,
          tag: 'Settings',
          title: 'Settings'
        }
      ]
    };
  }

  _keyExtrator = index => index.toString()

  _renderItem = ({ item, index }) => {
    return (
      <ListItem
        index={index}
        item={item}
        navigation={this.props.navigation}
      />
    )
  }

  render() {
    return (
      <View style={styles.homeBackground}>
        <View style={styles.banner}>
          <Text style={styles.bannerText}>Tap an icon and navigate through the menus</Text>
        </View>
        <FlatList
          contentContainerStyle={styles.grid}
          data={this.state.gridItems}
          keyExtractor={this._keyExtrator}
          numColumns={2}
          renderItem={this._renderItem}
        />
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