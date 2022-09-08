pipeline {
  agent none
  stages {
    stage('Building') {
        agent {
            docker { image 'sglahn/platformio-core:latest'}
        }
        steps {
            sh 'pio run'
        }
    }
    // stage('Testing') {
    //   agent {
    //     docker { image 'throwtheswitch/madsciencelab' }
    //   }
    //   steps {
    //     sh 'ceedling'
    //   }
    // }
  }
}