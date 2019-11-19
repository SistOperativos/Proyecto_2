import React from 'react';
import { createAppContainer, createSwitchNavigator } from 'react-navigation';

import homeScreen from '../screens/homeScreen/'
import GameScreen from  '../screens/gameScreen/'
export default createAppContainer(
  createSwitchNavigator({
    // You could add another route here for authentication.
    // Read more at https://reactnavigation.org/docs/en/auth-flow.html
    Home: homeScreen,
    GameScreen : GameScreen
  })
);
